#include "node_src.h"
#include <inttypes.h>
#include <assert.h>

#define BLOCK_INDENT 4

/* List of globals. */
int src_print_fileno = 1;

/* List of static variables. */
static int cur_col = 0;
static int cur_line = 0;
static size_t slen = 0;
static bool need_sep = false;

static int block_depth = 0;
static int expression_depth = 0;

#define NEWLINE do { need_sep = false; emit_str("\n"); cur_line++; cur_col = 0; } while(0)

/* Function prototypes. */
static void emit_expression(const node_t *n);
static void emit_statement(const node_t *n);
static void emit_block(const node_t *n);
static void emit_node(const node_t *n);

static const char *node_data_str(const node_t *n, size_t *len)
{
    static char st_buf[128];

    if (NODE_HAS_PRINTABLE_DATA(n)) {
        *len = strlen(n->data_char_ptr);
        return n->data_char_ptr;
    } else if (n->type == NUMBER_DATA) {
        int written = snprintf(st_buf, sizeof(st_buf), "%" PRIdit, n->data_integer);
        st_buf[written] = '\0';
        *len = written;
        return st_buf;
    }
    return "(UNKNOWN DATA)";
}

static void align_col(int *cur_col, int col) { while (*cur_col < col) { (*cur_col)++; dprintf(src_print_fileno, " "); } }

static void emit_str(const char *s) { if (!cur_col) { align_col(&cur_col, block_depth * BLOCK_INDENT); } else if (need_sep) { dprintf(src_print_fileno, " "); cur_col++; need_sep = false; } dprintf(src_print_fileno, "%s", s); cur_col += strlen(s); }
static void emit_number(const node_t *n) { emit_str(node_data_str(n, &slen)); need_sep = true; }
static void emit_ident(const node_t *n) { emit_str(node_data_str(n, &slen)); }

static void emit_variable_list(const node_t *n)
{
    for (uint64_t i = 0; i < n->n_children; i++) {
        emit_ident(n->children[i]);
        if (i + 1 < n->n_children) emit_str(", ");
    }
}

static void emit_params(const node_t *n)
{
    emit_str("(");
    emit_variable_list(n);
    emit_str(")");
}

static void emit_assignment_statement(const node_t *n)
{
    emit_ident(n->children[0]); need_sep = true;
    emit_str(":="); need_sep = true;
    emit_statement(n->children[1]);
    NEWLINE;
}

static void error(const char *msg, const node_t *node) { fprintf(stderr, "ERROR: %s, %s\n", msg, NODE_TO_TYPE_STRING(node)); exit(2); }

static void emit_arglist(const node_t *n)
{
    emit_str("(");
    for (uint64_t i = 0; i < n->n_children; i++) {
        emit_expression(n->children[i]); need_sep = false;
        if (i + 1 < n->n_children) emit_str(", ");
    }
    emit_str(")");
}

static void emit_expression(const node_t *n)
{
    expression_depth++;

    if (!strcmp(node_data_str(n, &slen), "func_call")) {
        emit_ident(n->children[0]);  need_sep = false;
        emit_arglist(n->children[1]);
    } else if (n->n_children == 1) {
        /* unary */
        if (expression_depth > 1) emit_str("(");
        emit_str(node_data_str(n, &slen));
        emit_expression(n->children[0]);
        need_sep = false;
        if (expression_depth > 1) emit_str(")");
    } else if (n->n_children == 2) {
        /* unary */
        if (expression_depth > 1) emit_str("(");
        emit_expression(n->children[0]); need_sep = true;
        emit_str(node_data_str(n, &slen)); need_sep = true;
        emit_expression(n->children[1]);
        need_sep = false;
        if (expression_depth > 1) emit_str(")");
    } else if (n->type == NUMBER_DATA) {
        emit_number(n);
    } else if (n->type == IDENTIFIER_DATA) {
        emit_ident(n);
    } else {
        error("Unexpected expression!", n);
    }
    need_sep = true;
    expression_depth--;
}

static void emit_return_statement(const node_t *n)
{
    if (cur_col) NEWLINE;
    emit_str("return"); need_sep = true;
    emit_expression(n->children[0]);
    NEWLINE;
}

static void emit_string(const node_t *n)
{
    emit_str(node_data_str(n, &slen));
}

static void emit_print_statement(const node_t *n)
{
    if (cur_col) NEWLINE;
    emit_str("print"); need_sep = true;
    for (uint64_t i = 0; i < n->n_children; i++) {
        if (n->children[i]->type == STRING_DATA) {
            emit_string(n->children[i]);
        } else {
            emit_expression(n->children[i]);
        }
        if (i + 1 < n->n_children) { need_sep = false; emit_str(", "); };
    }
    NEWLINE;
}

static void emit_declaration_list(const node_t *n)
{
    emit_str("var"); need_sep = true;
    emit_variable_list(n);
    NEWLINE;
}

static void emit_relation(const node_t *n)
{
    emit_expression(n->children[0]); need_sep = true;
    emit_str(node_data_str(n, &slen)); need_sep = true;
    emit_expression(n->children[1]); need_sep = true;
}

static void emit_if_statement(const node_t *n)
{
    emit_str("if"); need_sep = true;
    emit_relation(n->children[0]); need_sep = true;
    emit_str("then"); need_sep = true;

    block_depth++;
    emit_statement(n->children[1]); need_sep = true;
    block_depth--;

    if (n->n_children == 3) {
        emit_str("else"); need_sep = true;
        block_depth++;
        emit_statement(n->children[2]);
        block_depth--;
        need_sep = true;
    }
}

static void emit_while_statement(const node_t *n)
{
    emit_str("while"); need_sep = true;
    emit_relation(n->children[0]);
    emit_str("do"); need_sep = true;
    NEWLINE;
    emit_statement(n->children[1]); need_sep = true;
}

static void emit_statement(const node_t *n)
{
    if (!NODE_TYPE_IS_STATEMENT(n->type)) {
        if (NODE_TYPE_IS_EXPRESSION(n->type)) {
            emit_expression(n);
            return;
        }
    }

    switch (n->type) {
        case ASSIGNMENT_STATEMENT:  { emit_assignment_statement(n); return; break; };
        case RETURN_STATEMENT:      { emit_return_statement(n); break; };
        case PRINT_STATEMENT:       { emit_print_statement(n); break; };
        case NULL_STATEMENT:        { emit_str("continue"); break; };
        case IF_STATEMENT:          { emit_if_statement(n); break; };
        case WHILE_STATEMENT:       { emit_while_statement(n); break; };
        case BLOCK:                 { emit_block(n); break; };
        default: error("Unexpected statement type!", n);
    }
}

static void emit_statement_list(const node_t *n)
{
    /* Emit statement list */
    for (uint64_t i = 0; i < n->n_children; i++) {
        emit_statement(n->children[i]);
        need_sep = true;
    }
}

static void emit_block(const node_t *n)
{
    if (cur_col) NEWLINE;
    emit_str("begin"); need_sep = true;
    NEWLINE;
    block_depth++;

    for (uint64_t i = 0; i < n->n_children; i++) {
        switch (n->children[i]->type) {
            case DECLARATION_LIST: emit_declaration_list(n->children[i]); break;
            case VARIABLE_LIST: {
                /* is a declaration list */
                emit_str("var"); need_sep = true;
                emit_variable_list(n->children[i]);
                NEWLINE;
                break;
            }
            case STATEMENT_LIST: emit_statement_list(n->children[i]); break;
            default: error("Unexpected block child type: ", n->children[i]);
        }
    }

    block_depth--;
    if (cur_col) NEWLINE;
    emit_str("end");
    NEWLINE;

    need_sep = true;
}

static void emit_comment(const node_t *n)
{
    emit_str(n->data_char_ptr);
    NEWLINE;
}

static void emit_def(const node_t *n)
{
    if (n->comment) emit_comment(n->comment);

    emit_str("def"); need_sep = true;
    emit_ident(n->children[0]); need_sep = false;
    emit_params(n->children[1]); need_sep = true;
    NEWLINE;
    emit_node(n->children[2]);
}

static void emit_node(const node_t *n)
{
    switch (n->type) {
        case BLOCK:             emit_block(n); break;
        case FUNCTION:          emit_def(n); break;
        case DECLARATION_LIST:  emit_declaration_list(n); break;
        case VARIABLE_LIST:     emit_variable_list(n); break;
        case STATEMENT_LIST:    emit_statement_list(n); break;
        case EXPRESSION:        emit_expression(n); break;
        case STATEMENT:         emit_statement(n); break;
        case RETURN_STATEMENT:  emit_return_statement(n); break;
        case ASSIGNMENT_STATEMENT: emit_assignment_statement(n); break;
        default: error("Node type not handled yet!", n); break;
    }
}

void node_print_source(node_t *n)
{
    switch (n->type) {
        case VARIABLE_LIST: emit_declaration_list(n); NEWLINE; return; break;
        case DECLARATION_LIST: emit_declaration_list(n); NEWLINE; return; break;
        case FUNCTION: emit_def(n); NEWLINE; return; break;
        default: break;
    }

    for (uint64_t i = 0; i < n->n_children; i++)
        node_print_source(n->children[i]);
}

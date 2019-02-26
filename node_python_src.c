/*
 * "Complete" (for its current state) VSL to Python 3 transpiler.
 */

#include "node_python_src.h"
#include <inttypes.h>
#include <assert.h>

#include "vec.h"

#define BLOCK_INDENT 4

/* List of globals. */
int python_src_print_fileno = 1;

/* List of static variables. */
static int cur_col = 0;
static int cur_line = 0;
static size_t slen = 0;
static bool need_sep = false;

static int block_depth = 0;
static int expression_depth = 0;

struct scope {
    VEC(node_t_ptr) vars;
    bool is_while_loop;
};
typedef struct scope scope_t;

scope_t VEC_DEFAULT(scope_t) = {{0}, false};
DEF_VEC(scope_t, scope_t, VEC_DEFAULT(scope_t));

static bool block_scopes_inited = false;
static VEC(scope_t) block_scopes;

#define NEWLINE do { need_sep = false; emit_str("\n"); cur_line++; cur_col = 0; } while(0)

/* function prototypes */
static void emit_expression(const node_t *n);
static void emit_statement(const node_t *n);
static void emit_block(const node_t *n);

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

static void align_col(int *cur_col, int col) { while (*cur_col < col) { (*cur_col)++; dprintf(python_src_print_fileno, " "); } }

static void emit_str(const char *s) { if (!cur_col) { align_col(&cur_col, block_depth * BLOCK_INDENT); } else if (need_sep) { dprintf(python_src_print_fileno, " "); cur_col++; need_sep = false; } dprintf(python_src_print_fileno, "%s", s); cur_col += strlen(s); }
static void emit_number(const node_t *n) { emit_str(node_data_str(n, &slen)); need_sep = true; }
static void emit_ident(const node_t *n) { emit_str(node_data_str(n, &slen)); }

static void emit_variable_list(const node_t *n) {
    for (uint64_t i = 0; i < n->n_children; i++) {
        emit_ident(n->children[i]);
        if (i + 1 < n->n_children) emit_str(", ");
    }
}

static void emit_params(const node_t *n) {
    emit_str("(");
    emit_variable_list(n);
    emit_str(")");
}

static void error(const char *msg, const node_t *node) { fprintf(stderr, "ERROR: %s, %s\n", msg, NODE_TO_TYPE_STRING(node)); exit(2); }

static void emit_arglist(const node_t *n) {
    emit_str("(");
    for (uint64_t i = 0; i < n->n_children; i++) {
        emit_expression(n->children[i]); need_sep = false;
        if (i + 1 < n->n_children) emit_str(", ");
    }
    emit_str(")");
}

static void emit_expression(const node_t *n) {
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

        const char *expr = NULL;
        switch (*node_data_str(n, &slen)) {
            case '/': expr = "//"; break;
            case '*': expr = "*";  break;
            case '+': expr = "+";  break;
            case '-': expr = "-";  break;
        }
        emit_str(expr); need_sep = true;
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

static void emit_return_statement(const node_t *n) {
    if (cur_col) NEWLINE;
    if (block_depth > 1) {
        emit_str("return __BLOCK_RETURN___,"); need_sep = true;
    } else {
        emit_str("return"); need_sep = true;
    }
    emit_expression(n->children[0]);
    NEWLINE;
}

static void emit_string(const node_t *n) {
    emit_str(node_data_str(n, &slen));
}

static void emit_print_statement(const node_t *n) {
    if (cur_col) NEWLINE;
    emit_str("print("); need_sep = true;
    for (uint64_t i = 0; i < n->n_children; i++) {
        if (n->children[i]->type == STRING_DATA) {
            emit_string(n->children[i]);
        } else {
            emit_expression(n->children[i]);
        }
        if (i + 1 < n->n_children) { need_sep = false; emit_str(", "); };
    }
    emit_str(")");
    NEWLINE;
}

static void emit_declaration_list(const node_t *n) { (void) n;
/* handle globals ? */
    /* Initialize to None */
    for (uint64_t i = 0; i < n->n_children; i++) {
        emit_ident(n->children[i]);
        if (i + 1 < n->n_children) emit_str(", ");
    }
    emit_str(" = [0]*");
    dprintf(python_src_print_fileno, "%" PRIu64, n->n_children);
    return; }

static void emit_relation(const node_t *n) {
    emit_expression(n->children[0]); need_sep = true;

    char *out;
    switch (*node_data_str(n, &slen)) {
        case '=': out = "=="; break;
        case '<': out = "<";  break;
        case '>': out = ">";  break;
    }

    emit_str(out); need_sep = true;
    emit_expression(n->children[1]); need_sep = true;
}

static void emit_if_statement(const node_t *n) {
    if (cur_col) NEWLINE;
    emit_str("if"); need_sep = true;
    emit_relation(n->children[0]); need_sep = true;
    emit_str(":"); need_sep = true;

    block_depth++;
    emit_statement(n->children[1]); need_sep = true;
    block_depth--;

    if (n->n_children == 3) {
        if (cur_col) NEWLINE;
        emit_str("else:"); need_sep = true;
        if (cur_col) NEWLINE;
        block_depth++;
        emit_statement(n->children[2]);
        block_depth--;
        need_sep = true;
    }
}

static void emit_while_statement(const node_t *n) {
    if (cur_col) NEWLINE;

    VEC(node_t_ptr) scope_vars;
    VEC_INIT(&scope_vars, node_t_ptr);

    /* Push a new, empty scope with the while_loop bool set.
     * This is used when to handle continue statements.
     */
    VEC_PUSH(&block_scopes, scope_t, ((scope_t){scope_vars, true}));

    emit_str("while (");
    emit_relation(n->children[0]);
    emit_str("):");
    NEWLINE;
    block_depth++;
    emit_statement(n->children[1]); need_sep = true;
    block_depth--;

    VEC_POP(&block_scopes, scope_t);
    VEC_DESTROY(&scope_vars, node_t_ptr);
}

static void emit_null_statement(const node_t *n) {
    /* continue */

    /* If the closest scope is a while statement scope, then
     * just emit 'continue' directly. If not, then return with
     * the continue flag and let the callee (block) handle it further. */
    scope_t curr = VEC_PEEK(&block_scopes, scope_t);
    if (curr.is_while_loop) {
        emit_str("continue"); NEWLINE;
    } else {
        emit_str("return __BLOCK_CONTINUE___, None"); NEWLINE;
    }
}

static void emit_statement(const node_t *n) {
    if (!NODE_TYPE_IS_STATEMENT(n->type)) {
        //if (n->type == DECLARATION_LIST) {
        //    emit_declaration_list(n);
        //    return;
        //} else if (NODE_TYPE_IS_EXPRESSION(n->type)) {
        //    emit_expression(n);
        //    return;
        //}
        if (NODE_TYPE_IS_EXPRESSION(n->type)) {
            emit_expression(n);
            return;
        }
    }

    switch (n->type) {
        case ASSIGNMENT_STATEMENT:  { emit_ident(n->children[0]); need_sep = true; emit_str("="); need_sep = true; emit_statement(n->children[1]); NEWLINE; return; break; };
        case RETURN_STATEMENT:      { emit_return_statement(n); break; };
        case PRINT_STATEMENT:       { emit_print_statement(n); break; };
        case IF_STATEMENT:          { emit_if_statement(n); break; };
        case WHILE_STATEMENT:       { emit_while_statement(n); break; };
        case NULL_STATEMENT:        { emit_null_statement(n); break; };
        case BLOCK:                 { emit_block(n); break; };
        default: error("Unexpected statement type!", n);
    }
}

static void emit_statement_list(const node_t *n) {
    /* Emit statement list */
    for (uint64_t i = 0; i < n->n_children; i++) {
        emit_statement(n->children[i]);
        need_sep = true;
    }
}

static void emit_block(const node_t *n) {
    if (cur_col) NEWLINE;

    if (!block_scopes_inited) {
        VEC_INIT(&block_scopes, scope_t);
        block_scopes_inited = true;
        /* TODO: Destroy... */
    }

    VEC(node_t_ptr) scope_vars;
    VEC_INIT(&scope_vars, node_t_ptr);

    /* Save all identifiers which are introduced in
     * this scope in the scope_vars vector. */
    for (uint64_t i = 0; i < n->n_children; i++) {
        switch (n->children[i]->type) {
            case DECLARATION_LIST: {
                /* push vars to scope */
                for (uint64_t j = 0; j < n->children[i]->n_children; j++) {
                    assert(n->children[i]->children[j]->type == IDENTIFIER_DATA);
                    VEC_PUSH(&scope_vars, node_t_ptr, n->children[i]->children[j]);
                }
                break;
            }

            /*  emit_declaration_list(n->children[i]); */ break;
            case VARIABLE_LIST: {
                /* Push vars to scope.  */
                for (uint64_t j = 0; j < n->children[i]->n_children; j++) {
                    assert(n->children[i]->children[j]->type == IDENTIFIER_DATA);
                    VEC_PUSH(&scope_vars, node_t_ptr, n->children[i]->children[j]);
                }
                break;
            }
            default: break;
        }
    }

    if (block_depth == 0) {
        /* Add a default nonlocal to simplify the process since there is
         * no need to make sure that there exists any nonlocals before
         * printing 'nonlocal' anymore. */
        block_depth++;
        emit_str("__default_nonlocal___ = None");
        NEWLINE;
        block_depth--;
    }

    if (block_depth > 0) {
        /* Emulated block scopes by creating and calling
         * functions defined inside other functions. */
        emit_str("def block_");
        dprintf(python_src_print_fileno, "%d():", block_depth);
        NEWLINE;

        block_depth++; /* hack */

        /* Pass the declared variables of this current scope
         * (all vars lists above this one). */
         /* NOTE: May contain repeated identifiers. */
        for (uint64_t i = 0; i < VEC_LEN(&block_scopes); i++) {
                /* NOTE: this does not include the CURRENT SCOPE. */
            scope_t *scope = VEC_GET_PTR(&block_scopes, scope_t, i);
            if (!VEC_LEN(&scope->vars)) continue;

            emit_str("nonlocal __default_nonlocal___");
            for (uint64_t j = 0; j < VEC_LEN(&scope->vars); j++) {
                node_t *ptr = VEC_GET(&scope->vars, node_t_ptr, j);
                assert(ptr->type == IDENTIFIER_DATA);

                bool in_new_scope = false;
                /* TODO: Use hashmap.., this is very inefficient.. */
                for (uint64_t k = 0; k < VEC_LEN(&scope_vars); k++) {
                    node_t *n_ptr = VEC_GET(&scope_vars, node_t_ptr, k);
                    assert(n_ptr->type == IDENTIFIER_DATA);
                    if (!strcmp(n_ptr->data_char_ptr, ptr->data_char_ptr)) {
                        /* is declared in this NEW scope, so skip it */
                        in_new_scope = true;
                        break;
                    }
                }

                if (in_new_scope) continue;
                dprintf(python_src_print_fileno, ", %s", ptr->data_char_ptr);
            }
            NEWLINE;
        }
        block_depth--; /* hack */
    }
    block_depth++;
    assert(n->n_children >= 1);

    if (VEC_LEN(&scope_vars)) {
        /* Initialize identifiers to 0 (since all variables are ints...) to avoid problems where the identifier is
         * not used other than in nonlocal statements. */
        for (uint64_t i = 0; i < VEC_LEN(&scope_vars); i++) {
            emit_ident(VEC_GET(&scope_vars, node_t_ptr, i));
            if (i + 1 < VEC_LEN(&scope_vars)) emit_str(", ");
        }
        emit_str(" = [0]*");
        dprintf(python_src_print_fileno, "%" PRIu64, VEC_LEN(&scope_vars));
        NEWLINE;
    }

    VEC_PUSH(&block_scopes, scope_t, ((scope_t){scope_vars, false}));

    for (uint64_t i = 0; i < n->n_children; i++) {
        switch (n->children[i]->type) {
            case STATEMENT_LIST: emit_statement_list(n->children[i]); break;
            default: break;
        }
    }

    emit_str("return __BLOCK_DO_NOTHING___, None"); /* default return */

    block_depth--;

    VEC_POP(&block_scopes, scope_t);
    VEC_DESTROY(&scope_vars, node_t_ptr);

    if (cur_col) NEWLINE;

    if (block_depth > 0) {
        /* Call the created function. */
        emit_str("__ret_type___, __ret_val___ = block_");
        dprintf(python_src_print_fileno, "%d()", block_depth);
        NEWLINE;
        emit_str("if __ret_type___ == __BLOCK_RETURN___:"); NEWLINE;
        block_depth++;
        if (block_depth > 2) {
            emit_str("return __ret_type___, __ret_val___"); NEWLINE;
        } else {
            emit_str("return __ret_val___"); NEWLINE;
        }
        block_depth--;
        emit_str("elif __ret_type___ == __BLOCK_CONTINUE___:"); NEWLINE;
        block_depth++;

        {
            /* see emit_null_statement  */
            scope_t curr = VEC_PEEK(&block_scopes, scope_t);
            if (curr.is_while_loop) {
                emit_str("continue"); NEWLINE;
            } else {
                emit_str("return __BLOCK_CONTINUE___, None"); NEWLINE;
            }
        }
        emit_str("return __ret_val___"); NEWLINE;
        block_depth--;
    }

    NEWLINE;
    need_sep = true;
}

static void emit_comment(const node_t *n) {
    emit_str(n->data_char_ptr);
    NEWLINE;
}

static void emit_def(const node_t *n) {
    if (n->comment) emit_comment(n->comment);

    emit_str("def"); need_sep = true;
    emit_ident(n->children[0]); need_sep = false;
    emit_params(n->children[1]); need_sep = false;

    VEC(node_t_ptr) scope_vars;
    VEC_INIT(&scope_vars, node_t_ptr);

    /* push parameters to the block scopes vector */
    for (uint64_t i = 0; i < n->children[1]->n_children; i++) {
        VEC_PUSH(&scope_vars, node_t_ptr, n->children[1]->children[i]);
    }

    VEC_PUSH(&block_scopes, scope_t, ((scope_t){scope_vars, false}));

    emit_str(":");
    emit_block(n->children[2]);

    VEC_POP(&block_scopes, scope_t);
    VEC_DESTROY(&scope_vars, node_t_ptr);
}

static void recursive_transpile(node_t *n) {
    switch (n->type) {
        case VARIABLE_LIST: emit_declaration_list(n); NEWLINE; return; break;
        case DECLARATION_LIST: emit_declaration_list(n); NEWLINE; return; break;
        case FUNCTION: emit_def(n); NEWLINE; return; break;
        default: break;
    }

    for (uint64_t i = 0; i < n->n_children; i++)
        recursive_transpile(n->children[i]);
}

static node_t *find_main_func(node_t *root) {
    if (root->type == FUNCTION && !strcmp(node_data_str(root->children[0], &slen), "main"))
        return root;

    node_t *ret = NULL;
    for (uint64_t i = 0; i < root->n_children; i++)
        if ((ret = find_main_func(root->children[i]))) return ret;
    return NULL;
}

void transpile_to_python(node_t *n)
{
    /* Comment. */
    dprintf(python_src_print_fileno, "\"\"\""
        "\nTranspiled from vsl to python\n"
        "\"\"\"\n"
    );
    /* Import statements. */
    dprintf(python_src_print_fileno, "%s", "from sys import argv\n\n");

    /* Constants used by code generated by the transpiler. */
    dprintf(python_src_print_fileno, "__BLOCK_DO_NOTHING___ = 0"); NEWLINE;
    dprintf(python_src_print_fileno, "__BLOCK_CONTINUE___ = 1"); NEWLINE;
    dprintf(python_src_print_fileno, "__BLOCK_RETURN___ = 2"); NEWLINE;

    /* Transpile... */
    recursive_transpile(n);

    node_t *main_func = find_main_func(n);
    if (!main_func) {
        fprintf(stderr, "No main function defined!");
        return;
    }

    /* Create entry from main with the same amount of arguments. */
    dprintf(python_src_print_fileno, "if __name__ == '__main__':\n" "\t" "main(");

    for (uint64_t i = 0; i < main_func->children[1]->n_children; i++)
        dprintf(python_src_print_fileno, "int(argv[%" PRId64 "])%s", i + 1, i + 1 < main_func->children[1]->n_children ? ", " : "");

    dprintf(python_src_print_fileno, ")\n");

    if (block_scopes_inited) {
        block_scopes_inited = false;
        VEC_DESTROY(&block_scopes, scope_t);
    }
}

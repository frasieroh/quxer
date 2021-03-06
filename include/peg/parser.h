#include <inttypes.h>
#include "internal.h"
rnode_t* eval_grammar(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_ws(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_wsp(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_rule(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_name(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_body(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_alt(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_seq(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_operator(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_prefix(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_and(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_not(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_postfix(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_star(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_plus(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_option(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_group(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_final(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_nonterminal(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_literal(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_cclass(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_dot(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
rnode_t* eval_code(memo_state_t* state, uint8_t* text,
                 uint32_t text_length, uint32_t pos);
void semantic_action_0(context_t* context);
void alias_allocs_0(context_t* context);
void alias_frees_0(context_t* context);
void semantic_action_18(context_t* context);
void alias_allocs_18(context_t* context);
void alias_frees_18(context_t* context);
void semantic_action_31(context_t* context);
void alias_allocs_31(context_t* context);
void alias_frees_31(context_t* context);
void semantic_action_32(context_t* context);
void alias_allocs_32(context_t* context);
void alias_frees_32(context_t* context);
void semantic_action_40(context_t* context);
void alias_allocs_40(context_t* context);
void alias_frees_40(context_t* context);
void semantic_action_47(context_t* context);
void alias_allocs_47(context_t* context);
void alias_frees_47(context_t* context);
void semantic_action_57(context_t* context);
void alias_allocs_57(context_t* context);
void alias_frees_57(context_t* context);
void semantic_action_67(context_t* context);
void alias_allocs_67(context_t* context);
void alias_frees_67(context_t* context);
void semantic_action_78(context_t* context);
void alias_allocs_78(context_t* context);
void alias_frees_78(context_t* context);
void semantic_action_82(context_t* context);
void alias_allocs_82(context_t* context);
void alias_frees_82(context_t* context);
void semantic_action_89(context_t* context);
void alias_allocs_89(context_t* context);
void alias_frees_89(context_t* context);
void semantic_action_93(context_t* context);
void alias_allocs_93(context_t* context);
void alias_frees_93(context_t* context);
void semantic_action_97(context_t* context);
void alias_allocs_97(context_t* context);
void alias_frees_97(context_t* context);
void semantic_action_105(context_t* context);
void alias_allocs_105(context_t* context);
void alias_frees_105(context_t* context);
void semantic_action_111(context_t* context);
void alias_allocs_111(context_t* context);
void alias_frees_111(context_t* context);
void semantic_action_117(context_t* context);
void alias_allocs_117(context_t* context);
void alias_frees_117(context_t* context);
void semantic_action_119(context_t* context);
void alias_allocs_119(context_t* context);
void alias_frees_119(context_t* context);
void semantic_action_120(context_t* context);
void alias_allocs_120(context_t* context);
void alias_frees_120(context_t* context);
void semantic_action_121(context_t* context);
void alias_allocs_121(context_t* context);
void alias_frees_121(context_t* context);
void semantic_action_122(context_t* context);
void alias_allocs_122(context_t* context);
void alias_frees_122(context_t* context);
void semantic_action_124(context_t* context);
void alias_allocs_124(context_t* context);
void alias_frees_124(context_t* context);
void semantic_action_130(context_t* context);
void alias_allocs_130(context_t* context);
void alias_frees_130(context_t* context);
void semantic_action_131(context_t* context);
void alias_allocs_131(context_t* context);
void alias_frees_131(context_t* context);
void semantic_action_145(context_t* context);
void alias_allocs_145(context_t* context);
void alias_frees_145(context_t* context);
void semantic_action_159(context_t* context);
void alias_allocs_159(context_t* context);
void alias_frees_159(context_t* context);

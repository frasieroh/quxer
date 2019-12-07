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
void semantic_action_16(context_t* context);
void semantic_action_29(context_t* context);
void semantic_action_30(context_t* context);
void semantic_action_38(context_t* context);
void semantic_action_45(context_t* context);
void semantic_action_51(context_t* context);
void semantic_action_57(context_t* context);
void semantic_action_64(context_t* context);
void semantic_action_68(context_t* context);
void semantic_action_75(context_t* context);
void semantic_action_79(context_t* context);
void semantic_action_83(context_t* context);
void semantic_action_91(context_t* context);
void semantic_action_97(context_t* context);
void semantic_action_103(context_t* context);
void semantic_action_105(context_t* context);
void semantic_action_106(context_t* context);
void semantic_action_107(context_t* context);
void semantic_action_108(context_t* context);
void semantic_action_110(context_t* context);
void semantic_action_116(context_t* context);
void semantic_action_117(context_t* context);
void semantic_action_131(context_t* context);
void semantic_action_145(context_t* context);

#ifndef PEGSPEC_C
#define PEGSPEC_C

#include <stdarg.h>
#include <inttypes.h>

#include "peg/pegspec.h"

static pnode_t** pack_pnodes(pnode_t** buf, uint32_t count, ...)
{
    va_list ap;
    va_start(ap, count);
    for (int i = 0; i < count; ++i) {
        buf[i] = va_arg(ap, pnode_t*);
    }
    va_end(ap);
    return buf;
}

grammar_t* init_metagrammar()
/*
    This function was used to bootstrap the parser. It is no longer necessary
    because parser.c can parse this grammar directly from a file, but it's
    kept here for posterity. The present parser.c was generated from peg.txt
    in the root directory.
    ~grammar     = (ws r : rule)+ ws !. {{ result = ast_grammar(r, countr); }}
    
    ~ws          = (" " / "\n" / "\t")*
    
    ~wsp         = (" " / "\n" / "\t")+
    
    ~rule        = "~" <name> ws "=" ws b : body {{
      result = ast_rule(c(0), *b);
    }}
    
    ~name        = [A-Za-z0-9_]+
    
    ~body        = o : alt {{ result = *o; }}
    
    ~alt         = first : seq (ws "/" ws rest : seq)* {{
      result = ast_alt(first, rest, countrest + 1);
    }}

    ~seq         = first : operator (wsp rest : operator)* {{
      result = ast_seq(first, rest, countrest + 1);
    }}

    ~operator    = o : prefix (ws <code>)? {{
      if (ccount) { result = ast_with_code(c(0), *o); } else { result = *o; }
    }}
                 / o : postfix (ws <code>)? {{
      if (ccount) { result = ast_with_code(c(0), *o); } else { result = *o; }
    }}
                 / o : group (ws <code>)? {{
      if (ccount) { result = ast_with_code(c(0), *o); } else { result = *o; }
    }}

    ~prefix      = and ws o : group {{ result = ast_and(*o); }}
                 / not ws o : group {{ result = ast_not(*o); }}
    
    ~and         = "&"
    
    ~not         = "!"
    
    ~postfix     = o : group ws star {{ result = ast_star(*o); }}
                 / o : group ws plus {{ result = ast_plus(*o); }}
                 / o : group ws option {{ result = ast_option(*o); }}
    
    ~star        = "*"
    
    ~plus        = "+"
    
    ~option      = "?"
    
    ~group       = "(" ws o : body ws ")" {{ result = *o; }}
                 / "<" ws o : body ws ">" {{ result = ast_capture(*o); }}
                 / o : final {{ result = *o; }}
    
    ~final       = o : nonterminal {{ result = *o; }}
                 / o : literal {{ result = *o; }}
                 / o : cclass {{ result = *o; }}
                 / o : dot {{ result = *o; }}
    
    ~nonterminal = <name> ws ":" ws <name> {{
      result = ast_aliased_nontm(c(1), c(0));
    }}
                 / <name> {{
      result = ast_nontm(c(0));
    }}
    
    ~literal     = "\"" <(&"\\" . . / !"\"" .)*> "\"" {{
      result = ast_literal(c(0));
    }}
    
    ~cclass      = "[" <(&"\\" . . / !"]" .)*> "]" {{
      result = ast_CClass(c(0));
    }}
    
    ~dot         = "." {{ result = ast_dot(); }}
    
    ~code        = "{{" (&"\\" . . / !"}}" .)* "}}"
*/
{
        pnode_t* buf[16];
        // ~grammar
        pnode_t* temp1 = seq(2, pack_pnodes(buf, 2,
            nontm("ws"),
            aliased_nontm("rule", "r")
 		));
        rule_t* rule_grammar = init_rule("grammar",
            action(seq(3, pack_pnodes(buf, 3,
                    plus(temp1),
                    nontm("ws"),
                    not(range(0, 255)))),
                "result = ast_grammar(r, countr);")
        );
        // ~ws
        rule_t* rule_ws = init_rule("ws",
            star(alt(3, pack_pnodes(buf, 3,
                    literal(" "),
                    literal("\n"),
                    literal("\t"))))
        );
        // ~wsp
        rule_t* rule_wsp = init_rule("wsp",
            plus(alt(3, pack_pnodes(buf, 3,
                    literal(" "),
                    literal("\n"),
                    literal("\t"))
        )));
        // ~rule
        rule_t* rule_rule = init_rule("rule",
            action(seq(6, pack_pnodes(buf, 6,
                    literal("~"),
                    capture(nontm("name")),
                    nontm("ws"),
                    literal("="),
                    nontm("ws"),
                    aliased_nontm("body", "b"))),
                "result = ast_rule(c(0), *b);")
        );
        // ~name
        rule_t* rule_name = init_rule("name",
			plus(alt(4, pack_pnodes(buf, 4,
                    range('A', 'Z'),
                    range('a', 'z'),
                    range('0', '9'),
                    literal("_"))))
        );
        // ~body
        rule_t* rule_body = init_rule("body",
            action(
                aliased_nontm("alt", "o"),
                "result = *o;")
        );
        // ~alt
		temp1 = seq(4, pack_pnodes(buf, 4,
			nontm("ws"),
			literal("/"),
            nontm("ws"),
			aliased_nontm("seq", "rest")
        ));
        rule_t* rule_alt = init_rule("alt",
            action(seq(2, pack_pnodes(buf, 2,
                    aliased_nontm("seq", "first"),
                    star(temp1))),
                "result = ast_alt(first, rest, countrest + 1);")
		);
		// ~seq
		temp1 = seq(2, pack_pnodes(buf, 2,
            nontm("wsp"),
			aliased_nontm("operator", "rest")
        ));
        rule_t* rule_seq = init_rule("seq",
            action(seq(2, pack_pnodes(buf, 2,
                    aliased_nontm("operator", "first"),
                    star(temp1))),
                "result = ast_seq(first, rest, countrest + 1);")
		);
		// ~operator
        temp1 = option(seq(2, pack_pnodes(buf, 2,
                nontm("ws"),
                capture(nontm("code"))
        )));
        temp1 = action(seq(2, pack_pnodes(buf, 2,
                aliased_nontm("prefix","o"),
                option(temp1))),
            "if(ccount){result = ast_with_code(c(0), *o);}else{result = *o;}"
        );
        pnode_t* temp2 = option(seq(2, pack_pnodes(buf, 2,
                nontm("ws"),
                capture(nontm("code"))
        )));
        temp2 = action(seq(2, pack_pnodes(buf, 2,
                aliased_nontm("postfix","o"),
                option(temp2))),
            "if(ccount){result = ast_with_code(c(0), *o);}else{result = *o;}"
        );
        pnode_t* temp3 = option(seq(2, pack_pnodes(buf, 2,
                nontm("ws"),
                capture(nontm("code"))
        )));
        temp3 = action(seq(2, pack_pnodes(buf, 2,
                aliased_nontm("group","o"),
                option(temp3))),
            "if(ccount){result = ast_with_code(c(0), *o);}else{result = *o;}"
        );
        rule_t* rule_operator = init_rule("operator",
            alt(3, pack_pnodes(buf, 3,
                temp1,
                temp2,
                temp3))
        );
		// ~prefix
		temp1 = action(seq(3, pack_pnodes(buf, 3,
                nontm("and"),
                nontm("ws"),
                aliased_nontm("group", "o"))),
            "result = ast_and(*o);"
		);
		temp2 = action(seq(3, pack_pnodes(buf, 3,
                nontm("not"),
                nontm("ws"),
                aliased_nontm("group", "o"))),
            "result = ast_not(*o);"
		);
		rule_t* rule_prefix = init_rule("prefix",
			alt(2, pack_pnodes(buf, 2,
				temp1,
				temp2))
		);
		// ~and
		rule_t* rule_and = init_rule("and",
			literal("&")
		);
		// ~not
		rule_t* rule_not = init_rule("not",
			literal("!")
		);
		// ~postfix
		temp1 = action(seq(3, pack_pnodes(buf, 3,
                aliased_nontm("group", "o"),
                nontm("ws"),
                nontm("star"))),
            "result = ast_star(*o);"
		);
		temp2 = action(seq(3, pack_pnodes(buf, 3,
                aliased_nontm("group", "o"),
                nontm("ws"),
                nontm("plus"))),
            "result = ast_plus(*o);"
		);
		temp3 = action(seq(3, pack_pnodes(buf, 3,
                aliased_nontm("group", "o"),
                nontm("ws"),
                nontm("option"))),
            "result = ast_option(*o);"
		);
		rule_t* rule_postfix = init_rule("postfix",
			alt(3, pack_pnodes(buf, 3,
				temp1,
				temp2,
				temp3))
		);
		// ~star
		rule_t* rule_star = init_rule("star",
			literal("*")
		);
		// ~plus
		rule_t* rule_plus = init_rule("plus",
			literal("+")
		);
		// ~option
		rule_t* rule_option = init_rule("option",
			literal("?")
		);
		// ~group
		temp1 = action(seq(5, pack_pnodes(buf, 5,
                literal("("),
                nontm("ws"),
                aliased_nontm("body", "o"),
                nontm("ws"),
                literal(")"))),
            "result = *o;"
		);
		temp2 = action(seq(5, pack_pnodes(buf, 5,
                literal("<"),
                nontm("ws"),
                aliased_nontm("body", "o"),
                nontm("ws"),
                literal(">"))),
            "result = ast_capture(*o);"
		);
		rule_t* rule_group = init_rule("group",
			alt(3, pack_pnodes(buf, 3,
				temp1,
                temp2,
				action(
                    aliased_nontm("final", "o"),
                    "result = *o;")))
		);
		// ~final
		rule_t* rule_final = init_rule("final",
			alt(4, pack_pnodes(buf, 4,
				action(aliased_nontm("nonterminal", "o"), "result = *o;"),
                action(aliased_nontm("literal", "o"), "result = *o;"),
                action(aliased_nontm("cclass", "o"), "result = *o;"),
                action(aliased_nontm("dot", "o"), "result = *o;")))
		);
        // ~nonterminal
        temp1 = action(seq(5, pack_pnodes(buf, 5,
                capture(nontm("name")),
                nontm("ws"),
                literal(":"),
                nontm("ws"),
                capture(nontm("name")))),
            "result = ast_aliased_nontm(c(1), c(0));"
        );
        rule_t* rule_nonterminal = init_rule("nonterminal",
            alt(2, pack_pnodes(buf, 2,
                temp1,
                action(
                    capture(nontm("name")),
                    "result = ast_nontm(c(0));")))
        );
		// ~literal
		temp1 = seq(3, pack_pnodes(buf, 3,
			and(literal("\\")),
			range(0, 255),
			range(0, 255)
		));
		temp2 = seq(2, pack_pnodes(buf, 2,
			not(literal("\"")),
			range(0, 255)
		));
		temp3 = star(
			alt(2, pack_pnodes(buf, 2,
				temp1,
				temp2))
		);
		rule_t* rule_literal = init_rule("literal",
			action(seq(3, pack_pnodes(buf, 3,
                    literal("\""),
                    capture(temp3),
                    literal("\""))),
                "result = ast_literal(c(0));")
		);
		// ~cclass
		temp1 = seq(3, pack_pnodes(buf, 3,
			and(literal("\\")),
			range(0, 255),
			range(0, 255)
		));
		temp2 = seq(2, pack_pnodes(buf, 2,
			not(literal("]")),
			range(0, 255)
		));
		temp3 = star(
			alt(2, pack_pnodes(buf, 2,
				temp1,
				temp2))
		);
		rule_t* rule_cclass = init_rule("cclass",
			action(seq(3, pack_pnodes(buf, 3,
                    literal("["),
                    capture(temp3),
                    literal("]"))),
                "result = ast_CClass(c(0));")
		);
        // ~dot
		rule_t* rule_dot = init_rule("dot",
			action(literal("."),
            "result = ast_dot();")
		);
		// ~code
		temp1 = seq(3, pack_pnodes(buf, 3,
			and(literal("\\")),
			range(0, 255),
			range(0, 255)
		));
		temp2 = seq(2, pack_pnodes(buf, 2,
			not(literal("}}")),
			range(0, 255)
		));
		temp3 = star(
			alt(2, pack_pnodes(buf, 2,
				temp1,
				temp2))
		);
		rule_t* rule_code = init_rule("code",
			seq(3, pack_pnodes(buf, 3,
				literal("{{"),
				capture(temp3),
				literal("}}")))
		);
		rule_t* rules[23] = {
			rule_grammar,
			rule_ws,
	        rule_wsp,
            rule_rule,
			rule_name,
			rule_body,
			rule_alt,
			rule_seq,
			rule_operator,
			rule_prefix,
			rule_and,
			rule_not,
			rule_postfix,
			rule_star,
			rule_plus,
			rule_option,
			rule_group,
			rule_final,
            rule_nonterminal,
			rule_literal,
			rule_cclass,
            rule_code,
			rule_dot
		};
		return init_grammar(23, rules);
}

#endif


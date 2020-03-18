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
      result = ast_Alt(first, rest, countrest + 1);
    }}

    ~seq         = first : operator (wsp rest : operator)* {{
      result = ast_Seq(first, rest, countrest + 1);
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

    ~prefix      = and ws o : group {{ result = ast_And(*o); }}
                 / not ws o : group {{ result = ast_Not(*o); }}
    
    ~and         = "&"
    
    ~not         = "!"
    
    ~postfix     = o : group ws star {{ result = ast_Star(*o); }}
                 / o : group ws plus {{ result = ast_Plus(*o); }}
                 / o : group ws option {{ result = ast_Option(*o); }}
    
    ~star        = "*"
    
    ~plus        = "+"
    
    ~option      = "?"
    
    ~group       = "(" ws o : body ws ")" {{ result = *o; }}
                 / "<" ws o : body ws ">" {{ result = ast_Capture(*o); }}
                 / o : final {{ result = *o; }}
    
    ~final       = o : nonterminal {{ result = *o; }}
                 / o : literal {{ result = *o; }}
                 / o : cclass {{ result = *o; }}
                 / o : dot {{ result = *o; }}
    
    ~nonterminal = <name> ws ":" ws <name> {{
      result = ast_AliasedNontm(c(1), c(0));
    }}
                 / <name> {{
      result = ast_Nontm(c(0));
    }}
    
    ~literal     = "\"" <(&"\\" . . / !"\"" .)*> "\"" {{
      result = ast_Literal(c(0));
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
        pnode_t* temp1 = Seq(2, pack_pnodes(buf, 2,
            Nontm("ws"),
            AliasedNontm("rule", "r")
 		));
        rule_t* rule_grammar = init_rule("grammar",
            Action(Seq(3, pack_pnodes(buf, 3,
                    Plus(temp1),
                    Nontm("ws"),
                    Not(Range(0, 255)))),
                "result = ast_grammar(r, countr);")
        );
        // ~ws
        rule_t* rule_ws = init_rule("ws",
            Star(Alt(3, pack_pnodes(buf, 3,
                    Literal(" "),
                    Literal("\n"),
                    Literal("\t"))))
        );
        // ~wsp
        rule_t* rule_wsp = init_rule("wsp",
            Plus(Alt(3, pack_pnodes(buf, 3,
                    Literal(" "),
                    Literal("\n"),
                    Literal("\t"))
        )));
        // ~rule
        rule_t* rule_rule = init_rule("rule",
            Action(Seq(6, pack_pnodes(buf, 6,
                    Literal("~"),
                    Capture(Nontm("name")),
                    Nontm("ws"),
                    Literal("="),
                    Nontm("ws"),
                    AliasedNontm("body", "b"))),
                "result = ast_rule(c(0), *b);")
        );
        // ~name
        rule_t* rule_name = init_rule("name",
			Plus(Alt(4, pack_pnodes(buf, 4,
                    Range('A', 'Z'),
                    Range('a', 'z'),
                    Range('0', '9'),
                    Literal("_"))))
        );
        // ~body
        rule_t* rule_body = init_rule("body",
            Action(
                AliasedNontm("alt", "o"),
                "result = *o;")
        );
        // ~alt
		temp1 = Seq(4, pack_pnodes(buf, 4,
			Nontm("ws"),
			Literal("/"),
            Nontm("ws"),
			AliasedNontm("seq", "rest")
        ));
        rule_t* rule_alt = init_rule("alt",
            Action(Seq(2, pack_pnodes(buf, 2,
                    AliasedNontm("seq", "first"),
                    Star(temp1))),
                "result = ast_Alt(first, rest, countrest + 1);")
		);
		// ~seq
		temp1 = Seq(2, pack_pnodes(buf, 2,
            Nontm("wsp"),
			AliasedNontm("operator", "rest")
        ));
        rule_t* rule_seq = init_rule("seq",
            Action(Seq(2, pack_pnodes(buf, 2,
                    AliasedNontm("operator", "first"),
                    Star(temp1))),
                "result = ast_Seq(first, rest, countrest + 1);")
		);
		// ~operator
        temp1 = Option(Seq(2, pack_pnodes(buf, 2,
                Nontm("ws"),
                Capture(Nontm("code"))
        )));
        temp1 = Action(Seq(2, pack_pnodes(buf, 2,
                AliasedNontm("prefix","o"),
                Option(temp1))),
            "if(ccount){result = ast_with_code(c(0), *o);}else{result = *o;}"
        );
        pnode_t* temp2 = Option(Seq(2, pack_pnodes(buf, 2,
                Nontm("ws"),
                Capture(Nontm("code"))
        )));
        temp2 = Action(Seq(2, pack_pnodes(buf, 2,
                AliasedNontm("postfix","o"),
                Option(temp2))),
            "if(ccount){result = ast_with_code(c(0), *o);}else{result = *o;}"
        );
        pnode_t* temp3 = Option(Seq(2, pack_pnodes(buf, 2,
                Nontm("ws"),
                Capture(Nontm("code"))
        )));
        temp3 = Action(Seq(2, pack_pnodes(buf, 2,
                AliasedNontm("group","o"),
                Option(temp3))),
            "if(ccount){result = ast_with_code(c(0), *o);}else{result = *o;}"
        );
        rule_t* rule_operator = init_rule("operator",
            Alt(3, pack_pnodes(buf, 3,
                temp1,
                temp2,
                temp3))
        );
		// ~prefix
		temp1 = Action(Seq(3, pack_pnodes(buf, 3,
                Nontm("and"),
                Nontm("ws"),
                AliasedNontm("group", "o"))),
            "result = ast_And(*o);"
		);
		temp2 = Action(Seq(3, pack_pnodes(buf, 3,
                Nontm("not"),
                Nontm("ws"),
                AliasedNontm("group", "o"))),
            "result = ast_Not(*o);"
		);
		rule_t* rule_prefix = init_rule("prefix",
			Alt(2, pack_pnodes(buf, 2,
				temp1,
				temp2))
		);
		// ~and
		rule_t* rule_and = init_rule("and",
			Literal("&")
		);
		// ~not
		rule_t* rule_not = init_rule("not",
			Literal("!")
		);
		// ~postfix
		temp1 = Action(Seq(3, pack_pnodes(buf, 3,
                AliasedNontm("group", "o"),
                Nontm("ws"),
                Nontm("star"))),
            "result = ast_Star(*o);"
		);
		temp2 = Action(Seq(3, pack_pnodes(buf, 3,
                AliasedNontm("group", "o"),
                Nontm("ws"),
                Nontm("plus"))),
            "result = ast_Plus(*o);"
		);
		temp3 = Action(Seq(3, pack_pnodes(buf, 3,
                AliasedNontm("group", "o"),
                Nontm("ws"),
                Nontm("option"))),
            "result = ast_Option(*o);"
		);
		rule_t* rule_postfix = init_rule("postfix",
			Alt(3, pack_pnodes(buf, 3,
				temp1,
				temp2,
				temp3))
		);
		// ~star
		rule_t* rule_star = init_rule("star",
			Literal("*")
		);
		// ~plus
		rule_t* rule_plus = init_rule("plus",
			Literal("+")
		);
		// ~option
		rule_t* rule_option = init_rule("option",
			Literal("?")
		);
		// ~group
		temp1 = Action(Seq(5, pack_pnodes(buf, 5,
                Literal("("),
                Nontm("ws"),
                AliasedNontm("body", "o"),
                Nontm("ws"),
                Literal(")"))),
            "result = *o;"
		);
		temp2 = Action(Seq(5, pack_pnodes(buf, 5,
                Literal("<"),
                Nontm("ws"),
                AliasedNontm("body", "o"),
                Nontm("ws"),
                Literal(">"))),
            "result = ast_Capture(*o);"
		);
		rule_t* rule_group = init_rule("group",
			Alt(3, pack_pnodes(buf, 3,
				temp1,
                temp2,
				Action(
                    AliasedNontm("final", "o"),
                    "result = *o;")))
		);
		// ~final
		rule_t* rule_final = init_rule("final",
			Alt(4, pack_pnodes(buf, 4,
				Action(AliasedNontm("nonterminal", "o"), "result = *o;"),
                Action(AliasedNontm("literal", "o"), "result = *o;"),
                Action(AliasedNontm("cclass", "o"), "result = *o;"),
                Action(AliasedNontm("dot", "o"), "result = *o;")))
		);
        // ~nonterminal
        temp1 = Action(Seq(5, pack_pnodes(buf, 5,
                Capture(Nontm("name")),
                Nontm("ws"),
                Literal(":"),
                Nontm("ws"),
                Capture(Nontm("name")))),
            "result = ast_AliasedNontm(c(1), c(0));"
        );
        rule_t* rule_nonterminal = init_rule("nonterminal",
            Alt(2, pack_pnodes(buf, 2,
                temp1,
                Action(
                    Capture(Nontm("name")),
                    "result = ast_Nontm(c(0));")))
        );
		// ~literal
		temp1 = Seq(3, pack_pnodes(buf, 3,
			And(Literal("\\")),
			Range(0, 255),
			Range(0, 255)
		));
		temp2 = Seq(2, pack_pnodes(buf, 2,
			Not(Literal("\"")),
			Range(0, 255)
		));
		temp3 = Star(
			Alt(2, pack_pnodes(buf, 2,
				temp1,
				temp2))
		);
		rule_t* rule_literal = init_rule("literal",
			Action(Seq(3, pack_pnodes(buf, 3,
                    Literal("\""),
                    Capture(temp3),
                    Literal("\""))),
                "result = ast_Literal(c(0));")
		);
		// ~cclass
		temp1 = Seq(3, pack_pnodes(buf, 3,
			And(Literal("\\")),
			Range(0, 255),
			Range(0, 255)
		));
		temp2 = Seq(2, pack_pnodes(buf, 2,
			Not(Literal("]")),
			Range(0, 255)
		));
		temp3 = Star(
			Alt(2, pack_pnodes(buf, 2,
				temp1,
				temp2))
		);
		rule_t* rule_cclass = init_rule("cclass",
			Action(Seq(3, pack_pnodes(buf, 3,
                    Literal("["),
                    Capture(temp3),
                    Literal("]"))),
                "result = ast_CClass(c(0));")
		);
        // ~dot
		rule_t* rule_dot = init_rule("dot",
			Action(Literal("."),
            "result = ast_dot();")
		);
		// ~code
		temp1 = Seq(3, pack_pnodes(buf, 3,
			And(Literal("\\")),
			Range(0, 255),
			Range(0, 255)
		));
		temp2 = Seq(2, pack_pnodes(buf, 2,
			Not(Literal("}}")),
			Range(0, 255)
		));
		temp3 = Star(
			Alt(2, pack_pnodes(buf, 2,
				temp1,
				temp2))
		);
		rule_t* rule_code = init_rule("code",
			Seq(3, pack_pnodes(buf, 3,
				Literal("{{"),
				Capture(temp3),
				Literal("}}")))
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


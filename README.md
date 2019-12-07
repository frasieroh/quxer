# quxer
quxer generates dependency-free C99-compliant PEG packrat parsers from text
files in a domain-specific language similar to EBNF. Semantic actions may be
optionally embeded to construct an abstract syntax tree. The backend of the
parser writer was used to boostrap the parser, so the core of the program is
self-hosted.
## Compilation
Compile quxer with the standard cmake procedure:
```
mkdir build && cd build
CC=gcc cmake ..
make
```
The parsers quxer generates must also be compiled with `internal.c/h` in
`shared`. 
## Example
quxer is self-hosted, so a brief rundown of its inner workings are a good
example of its usage. Internally and prior to generation, grammars are
represented as a set of *parser trees* comprised of operators, terminals,
nonterminals, etc. A procedure traverses these trees with a bunch of templates
to write the resulting source file. Writing grammars symbolically in C is
tedious, so the challenge is to convert a text file into the symbolic
representation. PEGs themselves can be used to solve this problem! The following
grammar parses the grammar of PEGs and adds semantic actions to produce the
symbolic representation (technically, a wrapper around it):
```
~grammar     = (ws r : rule)+ ws {{ result = ast_grammar(r, countr); }}
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
```
This grammar was first written symbolically (in `src/peg/pegspec.c`) but the
current `parser.c` was generated directly from this text.
## Explanation
There are many resources for PEGs online to explain the basic stuff. Otherwise:
- Semantic actions are delimited by `{{ ... }}`.
- Rule definitions are prefixed with `~` but are referenced with their base name
  (this makes the grammar simpler).
- Nonterminals can be referenced in semantic actions with the syntax `alias :
  nonterminal`. A single nonterminal node may parse multiple times (if its
within a `*` or `+` operator), so `alias` is an array of the AST type. Its
length is given by `countalias`. Results are stored by assigning `result`. 
- You can capture by bracketing with `< ... >`. Captures are anonymous and done
  sequantially. The n-th capture (of type `uint8_t*`) is given by `c(n)`, its
start index `s(n)`, and its end index `e(n)`. The number of captures is given by
`ccount`.
- quxer employs a visitor pattern, that is, semantic actions are not evaluated
  until parsing is complete. Consequently semantic actions cannot provide live
updates on the parser's progress.
- When all is said and done, you can run your parser with `parse_file(char*
  filename)`. This links against `internal.h` which will start parsing at the
first grammar rule.
## TODO
- Add failure traces
- Add support for live actions

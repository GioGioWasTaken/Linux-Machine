#include <stdio.h>
int isNumber(char c);
enum Token_type {
  // Single-character tokens.
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,
  // One or two character tokens.
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,
  NUMBER,
  INVALID,
  EOF_token,
};

struct Token {
  enum Token_type type;
  char lexeme[50]; // allow numbers to have up to 50 sigfigs.
};
int isNumber(char c) { return (c >= '0' && c <= '9'); }

enum Token_type getTokenType(char c) {
  switch (c) {
  case '(':
    return LEFT_PAREN;
  case ')':
    return RIGHT_PAREN;
  case '{':
    return LEFT_BRACE;
  case '}':
    return RIGHT_BRACE;
  case ',':
    return COMMA;
  case '.':
    return DOT;
  case '-':
    return MINUS;
  case '+':
    return PLUS;
  case ';':
    return SEMICOLON;
  case '/':
    return SLASH;
  case '*':
    return STAR;
  case '=':
    return EQUAL;
  case '!':
    return BANG;
  case '>':
    return GREATER;
  case '<':
    return LESS;
  default:
    return INVALID;
  }
}

void tokenize(const char *expr, struct Token *Tokens) {
  int i = 0;
  int tokenIndex = 0;

  while (expr[i] != '\0') {
    char input = expr[i];
    Tokens[tokenIndex].type = getTokenType(input);

    // For numbers
    if (isNumber(input)) {
      int j = 0;
      // Store the entire number as the lexeme
      while (isNumber(input)) {
        Tokens[tokenIndex].lexeme[j++] = input; // current token's Lexeme
        // at the current character. After that, go to the next character.
        input = expr[++i]; // prepare next number character
      }
      Tokens[tokenIndex].lexeme[j] = '\0';
      Tokens[tokenIndex].type = NUMBER;
      tokenIndex++;
      continue;
    }

    // For other tokens
    if (Tokens[tokenIndex].type != INVALID) {
      Tokens[tokenIndex].lexeme[0] = input;
      Tokens[tokenIndex].lexeme[1] = '\0';
      tokenIndex++;
    }

    i++;
  }
  Tokens[tokenIndex].type = EOF_token; // End of file token
}

void printTokens(struct Token *Tokens) {
  for (int i = 0; Tokens[i].type != EOF_token; i++) {
    printf("Type: %d, Lexeme: %s\n", Tokens[i].type, Tokens[i].lexeme);
  }
}

int main() {
  struct Token Tokens[100];
  char expr[100];

  printf("Please enter your arithmetic expression: \n");
  scanf("%s", expr);

  tokenize(expr, Tokens);
  printTokens(Tokens);

  return 0;
}

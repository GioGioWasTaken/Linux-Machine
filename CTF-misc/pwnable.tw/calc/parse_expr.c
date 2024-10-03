int __cdecl parse_expr(int expression, _DWORD *operations)
{
  int v3; // eax
  int v4; // [esp+20h] [ebp-88h]
  int i; // [esp+24h] [ebp-84h]
  int v6; // [esp+28h] [ebp-80h]
  int v7; // [esp+2Ch] [ebp-7Ch]
  char *s1; // [esp+30h] [ebp-78h]
  int num; // [esp+34h] [ebp-74h]
  _BYTE s[100]; // [esp+38h] [ebp-70h] BYREF
  unsigned int v11; // [esp+9Ch] [ebp-Ch]

  v11 = __readgsdword(0x14u);
  v4 = expression;
  v6 = 0;
  bzero(s, 0x64u);
  for ( i = 0; ; ++i )
  {
    if ( (unsigned int)(*(char *)(i + expression) - 48) > 9 )// If it's an operation (and NaN)
    {
      v7 = i + expression - v4;
      s1 = (char *)malloc(v7 + 1);
      memcpy(s1, v4, v7);
      s1[v7] = 0;
      if ( !strcmp(s1, "0") )
      {
        puts("prevent division by zero");
        fflush(stdout);
        return 0;
      }
      num = atoi(s1);
      if ( num > 0 )
      {
        v3 = (*operations)++;
        operations[v3 + 1] = num;
      }
      if ( *(_BYTE *)(i + expression) && (unsigned int)(*(char *)(i + 1 + expression) - 48) > 9 )
      {
        puts("expression error!");
        fflush(stdout);
        return 0;
      }
      v4 = i + 1 + expression;
      if ( s[v6] )
      {
        switch ( *(_BYTE *)(i + expression) )
        {
          case '%':
          case '*':
          case '/':
            if ( s[v6] != 43 && s[v6] != 45 )
              goto LABEL_14;
            s[++v6] = *(_BYTE *)(i + expression);
            break;
          case '+':
          case '-':
LABEL_14:
            eval(operations, (char)s[v6]);
            s[v6] = *(_BYTE *)(i + expression);
            break;
          default:
            eval(operations, (char)s[v6--]);
            break;
        }
      }
      else
      {
        s[v6] = *(_BYTE *)(i + expression);
      }
      if ( !*(_BYTE *)(i + expression) )
        break;
    }
  }
  while ( v6 >= 0 )
    eval(operations, (char)s[v6--]);
  return 1;
}



_DWORD *__cdecl eval(_DWORD *a1, char a2)
{
  _DWORD *result; // eax

  if ( a2 == 43 )
  {
    a1[*a1 - 1] += a1[*a1];
  }
  else if ( a2 > 43 )
  {
    if ( a2 == 45 )
    {
      a1[*a1 - 1] -= a1[*a1];
    }
    else if ( a2 == 47 )
    {
      a1[*a1 - 1] /= (int)a1[*a1];
    }
  }
  else if ( a2 == 42 )
  {
    a1[*a1 - 1] *= a1[*a1];
  }
  result = a1;
  --*a1;
  return result;
}

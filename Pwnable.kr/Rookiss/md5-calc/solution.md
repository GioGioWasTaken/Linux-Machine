# Program flow

After some reversing, this is the "original code" i believe was there: 

```C
unsigned int process_hash()
{
    int length; // [esp+14h] [ebp-214h]
    char *ptr; // [esp+18h] [ebp-210h]
    _BYTE decoded_buf[512]; // [esp+1Ch] [ebp-20Ch] BYREF
    unsigned int canary; // [esp+21Ch] [ebp-Ch]

    canary = __readgsdword(0x14u);
    memset(decoded_buf, 0, sizeof(decoded_buf));
    while ( getchar() != '\n' )
        ;
    memset(base_64_input, 0, sizeof(base_64_input));
    fgets(base_64_input, 1024, stdin);
    memset(decoded_buf, 0, sizeof(decoded_buf));
    length = Base64Decode(base_64_input, decoded_buf);
    ptr = calc_md5(decoded_buf, length);
    printf("MD5(data) : %s\n", ptr);
    free(ptr);
    return __readgsdword(0x14u) ^ canary;
}
```

```C

char *__cdecl calc_md5(int decoded_buf, int length)
{
    _BYTE MD5_CTX[92]; // [esp+28h] [ebp-80h] BYREF
    int i; // [esp+84h] [ebp-24h]
    char *md5_str; // [esp+88h] [ebp-20h]
    _BYTE hash_buf[16]; // [esp+8Ch] [ebp-1Ch] BYREF
    unsigned int canary; // [esp+9Ch] [ebp-Ch]

    canary = __readgsdword(0x14u);
    md5_str = malloc(0x21u);
    MD5_Init(MD5_CTX);
    while ( length > 0 )
    {
        if ( length <= 512 )
            MD5_Update(MD5_CTX, decoded_buf, length);
        else
            MD5_Update(MD5_CTX, decoded_buf, 512);
        length -= 512;
        decoded_buf += 512;
    }
    MD5_Final(hash_buf, MD5_CTX);
    for ( i = 0; i <= 15; ++i )
        snprintf(&md5_str[2 * i], 0x20u, "%02x", hash_buf[i]);
    return md5_str;
}

```


Hm.... Seems normal?



```C
int __cdecl Base64Decode(const char *base_64_input, int decoded_buf)
{
    int v2; // eax
    int v3; // eax
    int length; // [esp+2Ch] [ebp-1Ch]
    FILE *stream; // [esp+34h] [ebp-14h]
    int v7; // [esp+38h] [ebp-10h]
    int v8; // [esp+3Ch] [ebp-Ch]

    length = calcDecodeLength(base_64_input);
    stream = fmemopen(base_64_input, strlen(base_64_input), &unk_8049272);
    v2 = BIO_f_base64();
    v7 = BIO_new(v2);
    v3 = BIO_new_fp(stream, 0);
    v8 = BIO_push(v7, v3);
    BIO_set_flags(v8, 256);
    *(decoded_buf + BIO_read(v8, decoded_buf, strlen(base_64_input))) = 0;
    BIO_free_all(v8);
    fclose(stream);
    return length;
}
```

Ah!, Bio_read doesn't have any length check. it just assumes the decoded value will fit inside the buffer given to it. 

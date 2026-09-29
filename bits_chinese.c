/* 警告：不要在这里包含任何其他库，
 * 否则运行 test.py 时会报错。
 * 你仍然可以使用 printf 进行调试，而无需包含
 * <stdio.h>，不过可能会收到编译器警告。一般来说，
 * 忽略编译器警告不是好习惯，但在这种
 * 情况下是可以的。
 *
 * 使用 printf 会干扰我们捕获执行结果的脚本。
 * 在现阶段，你只能用 ./btest 测试正确性。
 * 在 ./btest 中确认一切正确之后，请移除 printf，
 * 然后用 test.py 运行完整测试。
 */

 /*
 * bitAnd - 仅使用 ~ 和 | 实现 x & y
 * 示例：bitAnd(4, 5) = 4
 * 100
 * 101
 * 合法运算符：~ |
 * 最大运算符数：7
 * 难度：1
 */
//有x&y = ~(~x | ~y)
int bitAnd(int x, int y) {
    return ~(~x | ~y);
    //return 2;
}

/*
 * bitXor - 仅使用 ~ 和 & 实现 x ^ y.  异或
 *   示例：bitXor(4, 5) = 1
 *   合法运算符：~ &
 *   最大运算符数：7
 *   难度：1
 */
int bitXor(int x, int y) {
    //return (x & ~y) | (~x & y);
    //return ~(~(x & ~y) & ~(~x & y));
    //意味着两个不同时，为0
    return ~(x & y) & ~(~x & ~y);
}

/*
 * samesign - 判断两个整数是否具有相同的符号。
 *   0 既不是正数，也不是负数
 *   示例：samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   合法运算符：>> << ! ^ && if else &
 *   最大运算符数：12
 *   难度：2
 *
 * 参数：
 *   x - 第一个整数。
 *   y - 第二个整数。
 *
 * 返回值：
 *   如果 x 和 y 符号相同则返回 1，否则返回 0。
 */
int samesign(int x, int y) {
    //return 2;
    if(x==0 && y==0)
    {
        return 1;
    }
    if(x==0)
    {
        return 0;
    }
    if(y==0)
    {
        return 0;
    }
    return (x>>31 )&(y>>31);
}

/*
 * logtwo - 使用位移计算正整数的以 2 为底的对数。
 *   （想一想 bitCount）
 *   注意：可以假设 v > 0
 *   示例：logtwo(32) = 5
 *   合法运算符：> < >> << |
 *   最大运算符数：25
 *   难度：4
 */
int logtwo(int v) {
    //return v & (~(v - 1));坏了，这是找到最低位
    //使用二分法，先判断高16位是否为0，如果不为0，则说明最高位在高16位，否则在低16位
    //不允许使用 +，这里可以改成 |=
    int result = 0;
    int shift = ((v>>16)>0)<<4;
    result|=shift;
    v=v>>shift;
    shift = ((v>>8)>0)<<3;
    result|=shift;
    v=v>>shift;

    shift = ((v>>4)>0)<<2;
    result|=shift;
    v=v>>shift;
    shift = ((v>>2)>0)<<1;
    result|=shift;
    v=v>>shift;
    shift = ((v>>1)>0);
    result|=shift;
    return result;

    //return 2;
}

/*
 *  byteSwap - 交换第 n 个字节和第 m 个字节
 *    示例：byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    注意：可以假设 0 <= n <= 3, 0 <= m <= 3
 *    合法运算符：! ~ & ^ | + << >>
 *    最大运算符数：17
 *    难度：2
 */
int byteSwap(int x, int n, int m) {
    //int byte_n = (x>>n*8) & 0xFF;
    //但是✖️8使用了乘法运算符，所以我们可以使用位移来代替乘法
    int byte_n = (x>>(n<<3)) & 0xFF;
    int byte_m = (x>>(m<<3)) & 0xFF;
    //然后要替换掉第m个字节和第n个字节，我们可以先将这两个字节清零，然后再将它们放回去
    int mask_n =0xFF<<(n<<3);
    int mask_m =0xFF<<(m<<3);
    //int mask = ~(mask_n | mask_m);
    //这里可以写成异或
    int mask = mask_n ^ mask_m;
    int x_cleared = x & mask;
    //然后将byte_n和byte_m放回去
    int result = x_cleared | (byte_n<<(m<<3)) | (byte_m<<(n<<3));
    return result;

    //思路二：使用异或
    /*
    int byteSwap(int x, int n, int m) {
    int ns = n << 3;
    int ms = m << 3;
    int diff = (x >> ns) ^ (x >> ms);

    return x ^ ((diff & 0xFFu) << ns)
             ^ ((diff & 0xFFu) << ms);
}
    */

    //return 2;
}

/*
 * reverse - 反转一个 32 位无符号整数的比特顺序。
 *   示例：reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   注意：可以假设一个无符号整数为 32 位长。
 *   合法运算符：<< | & - + >> for while ! ~（你可以在本函数中定义 unsigned）
 *   最大运算符数：30
 *   难度：3
 */
//要求：把 32 位二进制从左到右完全镜像反转
unsigned reverse(unsigned v) {
    /*
    for(int i=0;i<16;i++)
    {
        //交换第i位和第31-i位
        unsigned bit_i = (v>>i) & 1;
        unsigned bit_31_i = (v>>(31-i)) & 1;
        if(bit_i != bit_31_i)
        {
            //如果不相等，就是异或，直接翻转
            v = v ^ (1<<i);
            v = v ^ (1<<(31-i));
        }
    }*/
    unsigned result = 0;
    int remaining = 32;

    while (remaining) {
        result = (result << 1) | (v & 1);
        v >>= 1;
        remaining -= 1;
    }

    return result;


    //return 2;
}

/*
 * logicalShift - 将 x 逻辑右移 n 位
 *   示例：logicalShift(0x87654321,4) = 0x08765432
 *   注意：可以假设 0 <= n <= 31
 *   合法运算符：! ~ & ^ | + << >>
 *   最大运算符数：20
 *   难度：3
 */
int logicalShift(int x, int n) {
    //借鉴取反的思路
    int mask = ~(((1 << 31) >> n) << 1);
    //int mask =( 1<<(32-n)-1);
    x =(x>>n);
    return (x & mask);
    //return 2;
}

/*
 * leftBitCount - 返回字长左端（最高位）连续 1 的个数。
 *   示例：leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   合法运算符：! ~ & ^ | + << >>
 *   最大运算符数：50
 *   难度：4
 */
int leftBitCount(int x) {
    /* 负数的符号位已经是 1。取反后寻找最高的 1，
     * 就能定位原数从左往右的第一个 0。屏蔽符号位，保证右移对象非负。
     */
    int v = ~x & 0x7FFFFFFF;
    int all_ones = !v;
    int n = 0;
    int shift = (!!(v >> 16)) << 4;
    n += shift;
    v >>= shift;
    shift = (!!(v >> 8)) << 3;
    n += shift;
    v >>= shift;
    shift = (!!(v >> 4)) << 2;
    n += shift;
    v >>= shift;
    shift = (!!(v >> 2)) << 1;
    n += shift;
    v >>= shift;
    n += !!(v >> 1);
    /* 通常答案是 31 - n；全 1 时再加 1。非负数用符号掩码归零。 */
    return (x >> 31) & (31 + (~n + 1) + all_ones);
}

/*
 * float_i2f - 返回表达式 (float) x 的位级等价表示
 *   结果以 unsigned int 返回，但它应被解释为
 *   单精度浮点数值的位级表示。
 *   合法运算符：if else while for & | ~ + - >> << < > ! ==
 *   最大运算符数：30
 *   难度：4
 */
unsigned float_i2f(int x) {
    unsigned sign = 0;
    unsigned magnitude;
    unsigned fraction;
    unsigned remainder;
    int exponent = 158;
    if (!x)
        return 0;
    /* INT_MIN 的绝对值不能用 int 表示，直接返回 -2^31 的编码。 */
    if (x == (-2147483647 - 1))
        return 0xCF000000u;
    if (x < 0) {
        sign = 0x80000000u;
        x = -x;
    }
    magnitude = x;
    /* 将最高有效位移到第 31 位；指数初值为 31 + 127。 */
    while (!(magnitude & 0x80000000u)) {
        magnitude <<= 1;
        exponent -= 1;
    }
    fraction = (magnitude >> 8) & 0x7FFFFFu;
    remainder = magnitude & 0xFFu;
    /* 丢弃低 8 位：超过一半向上舍入，恰好一半时使保留部分为偶数。 */
    if (remainder > 0x80u)
        fraction += 1;
    else if (remainder == 0x80u)
        fraction += fraction & 1;
    /* 用加法拼接指数和尾数，让尾数舍入溢出自然进位到指数。 */
    return sign | ((exponent << 23) + fraction);
}

/*
 * floatScale2 - 返回表达式 2*f 的位级等价表示，
 *   其中 f 为浮点参数。
 *   参数和返回值都以 unsigned int 传递，但它们
 *   应被解释为单精度浮点数值的位级表示。
 *   当参数为 NaN 时，返回该参数
 *   合法运算符：& >> << | if > < >= <= ! ~ else + ==
 *   最大运算符数：30
 *   难度：4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000u;
    unsigned exponent = uf & 0x7F800000u;
    unsigned fraction = uf & 0x007FFFFFu;
    /* 无穷和 NaN 原样返回，保留 NaN 的原始位模式。 */
    if (exponent == 0x7F800000u)
        return uf;
    /* 非规格化数直接将尾数乘 2，必要时自然进入规格化范围；保留零的符号。 */
    if (!exponent)
        return sign | (fraction << 1);
    exponent += 0x00800000u;
    /* 指数溢出时必须清空尾数，否则会错误地产生 NaN。 */
    if (exponent == 0x7F800000u)
        return sign | exponent;
    return sign | exponent | fraction;
}

/*
 * float64_f2i - 将 64 位 IEEE 754 浮点数转换为 32 位有符号整数。
 *   转换采用向零取整。
 *   注意：假定使用 IEEE 754 表示法和标准二进制补码整数格式。
 *   参数：
 *     uf1 - 64 位浮点数的低 32 位。
 *     uf2 - 64 位浮点数的高 32 位。
 *   返回值：
 *     转换后的整数值；溢出时返回 0x80000000，下溢时返回 0。
 *   合法运算符：>> << | & ~ ! + - > < >= <= if else
 *   最大运算符数：60
 *   难度：3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    //先构建一个mask
    unsigned mask = 0x7FFFFFFF;   //0111。。。
    //然后将uf1和uf2组合成一个64位的数
    unsigned long long num = ((unsigned long long)uf2 << 32) | uf1;
    //将num的符号位清零
    num &= mask;
    //将num转换为32位整数
    int result = (int)num;
    return result;
    return 2;
}

/*
 * floatPower2 - 对任意 32 位整数 x，返回表达式 2.0^x
 *   （2.0 的 x 次幂）的位级等价表示。
 *
 *   返回的无符号值应与单精度浮点数 2.0^x 具有
 *   完全相同的位表示。
 *   如果结果太小而无法表示为非规格化数，返回
 *   0。如果太大，返回 +INF。
 *
 *   合法运算符：< > <= >= << >> + - & | ~ ! if else &&
 *   最大运算符数：30
 *   难度：4
 */
unsigned floatPower2(int x) {
    /* 单精度最小正数是 2^-149，最大规格化指数是 127。 */
    if (x < -149)
        return 0;
    if (x > 127)
        return 0x7F800000u;
    /* 非规格化数的第 k 个尾数位表示 2^(k-149)。 */
    if (x < -126)
        return 1u << (x + 149);
    /* 规格化的 2^x 尾数为 0，指数域为 x + 127。 */
    return (x + 127) << 23;
}

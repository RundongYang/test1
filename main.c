# include "miracl.h"                    //调用大整数库miracl.h  
# include <time.h>  
# include <windows.h>
# include "math.h"  
# define TIMES 1000  

int prime_test(big n);  //进行一次判断是否为素数  
int is_prime(big n);  //进行TIMES次素性检测  
long reduce(big n);  //分解n-1  
big find_prime(long len, int m);//找len位m进制的大素数  

/************************************主函数**************************************************/
int main(void) {
	big n;
	miracl *mip = mirsys(65535, 10);        //最大65535位,输入输出使用10进制  
												
	n = mirvar(0);  //初始化  
	printf("************************$声明信息$****************************\n");
	printf("版权声明：未经授权，禁止传播、使用和用于商业用途\n");
	printf("使用说明：本程序是大数素性检测算法演示程序，直接输入要检测的大整数\n");
	printf("**********************$声明信息$******************************\n");
	printf("================大数素性检测算法演示================\n\n");
	printf("请输入要检测的大数：");
	cinnum(n, stdin);
	mip->IOBASE = 10;
	cotnum(n, stdout);

	if (isprime(n))
		printf("该大整数是素数！\n");
	else
		printf("该大整数不是素数！\n");

	//释放内存  
	mirkill(n);
	mirexit();
	system("pause");
	return (0);
}

/*********************************************素判定*************************************************/
//如果是素数，返回1，如果不是返回0  
int prime_test(big n) {
	big a, b, m, g, num, tmp;
	long i = 0, j = 0, k = 0;

	//初始化  
	a = mirvar(0);
	b = mirvar(0);
	m = mirvar(0);
	g = mirvar(0);
	num = mirvar(1);
	tmp = mirvar(2);

	//判断n是否为大于2的奇数，如果是偶数，返回0  
	//convert(2, a);  
	if (subdivisible(n, 2) && (mr_compare(n, tmp) == 1)) {
		return (0);
	}
	else {
		//分解n-1  
		k = reduce(n);
		decr(n, 1, b);
		sftbit(b, (-1)*k, m);

		//随机生成一个小于b的大数，判断是否为n的既约剩余系中的元素  
		do {
			bigrand(b, a);
			egcd(n, a, b);
			//convert(1, g);  
		} while (mr_compare(b, num) != 0);

		//计算a^m = b (mod n)  
		powmod(a, m, n, b);
		if (mr_compare(b, num) == 0)
			return (1);
		else {
			//convert(2, g);  
			//寻找最小的j  
			for (i = 0; i<k; i++) {
				copy(b, a);
				powmod(b, tmp, n, b);
				if (mr_compare(b, num) == 0) {
					j = i;
					break;
				}
			}
			for (i = j; i<k; i++) {
				powmod(b, num, n, b);
			}
			if (mr_compare(b, num) != 0)
				return (0);

			egcd(n, a, g);
			if ((mr_compare(n, g) == 0) || (mr_compare(g, num) == 0))
				return (1);
			else
				return (0);
		}
	}
	mirkill(a);
	mirkill(b);
	mirkill(m);
	mirkill(g);
	mirkill(num);
	mirkill(tmp);

	return (0);
}

//分解n  
long reduce(big n) {
	big tmp;
	long k = 0;
	tmp = mirvar(0);

	decr(n, 1, tmp);
	while (subdivisible(tmp, 2)) {
		sftbit(tmp, -1, tmp);
		k++;
	}
	mirkill(tmp);

	return (k);
}

//进行TIMES次素性检测  
int is_prime(big n) {
	long i = 0, sum = 0;
	for (i = 0; i<TIMES; i++) {
		if (prime_test(n)) {
			sum++;
			continue;
		}
		else
			break;
	}

	if (sum == TIMES)
		return (1);
	else
		return (0);
}

//找大素数  
big find_prime(long len, int m) {
	big res;
	res = mirvar(0);
	bigdig(len, m, res);

	while (!is_prime(res))
		bigdig(len, m, res);

	return (res);
}
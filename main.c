# include "miracl.h"                    //���ô�������miracl.h  
# include <time.h>  
# include <windows.h>
# include "math.h"  
# define TIMES 1000  

int prime_test(big n);  //����һ���ж��Ƿ�Ϊ����  
int is_prime(big n);  //����TIMES�����Լ��  
long reduce(big n);  //�ֽ�n-1  
big find_prime(long len, int m);//��lenλm���ƵĴ�����  

/************************************������**************************************************/
int main(void) {
	big n;
	miracl *mip = mirsys(65535, 10);        //���65535λ,�������ʹ��10����  
												
	n = mirvar(0);  //��ʼ��  
	printf("************************$������Ϣ$****************************\n");
	printf("��Ȩ������δ����Ȩ����ֹ������ʹ�ú�������ҵ��;\n");
	printf("ʹ��˵�����������Ǵ������Լ���㷨��ʾ����ֱ������Ҫ���Ĵ�����\n");
	printf("**********************$������Ϣ$******************************\n");
	printf("================�������Լ���㷨��ʾ================\n\n");
	printf("������Ҫ���Ĵ�����");
	cinnum(n, stdin);
	mip->IOBASE = 10;
	cotnum(n, stdout);

	if (isprime(n))
		printf("�ô�������������\n");
	else
		printf("�ô���������������\n");

	//�ͷ��ڴ�  
	mirkill(n);
	mirexit();
	system("pause");
	return (0);
}

/*********************************************���ж�*************************************************/
//���������������1��������Ƿ���0  
int prime_test(big n) {
	big a, b, m, g, num, tmp;
	long i = 0, j = 0, k = 0;

	//��ʼ��  
	a = mirvar(0);
	b = mirvar(0);
	m = mirvar(0);
	g = mirvar(0);
	num = mirvar(1);
	tmp = mirvar(2);

	//�ж�n�Ƿ�Ϊ����2�������������ż��������0  
	//convert(2, a);  
	if (subdivisible(n, 2) && (mr_compare(n, tmp) == 1)) {
		return (0);
	}
	else {
		//�ֽ�n-1  
		k = reduce(n);
		decr(n, 1, b);
		sftbit(b, (-1)*k, m);

		//�������һ��С��b�Ĵ������ж��Ƿ�Ϊn�ļ�Լʣ��ϵ�е�Ԫ��  
		do {
			bigrand(b, a);
			egcd(n, a, b);
			//convert(1, g);  
		} while (mr_compare(b, num) != 0);

		//����a^m = b (mod n)  
		powmod(a, m, n, b);
		if (mr_compare(b, num) == 0)
			return (1);
		else {
			//convert(2, g);  
			//Ѱ����С��j  
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

//�ֽ�n  
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

//����TIMES�����Լ��  
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

//�Ҵ�����  
big find_prime(long len, int m) {
	big res;
	res = mirvar(0);
	bigdig(len, m, res);

	while (!is_prime(res))
		bigdig(len, m, res);

	return (res);
}
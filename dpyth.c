#include <math.h>
#include <Python.h>
#include <stdlib.h>


int Factorial(int n)
{
	if (n < 0)
		return -1;
	if ((n==0)||(n==1))
		return 1;
	return n*Factorial(n-1);
}

int Factorial2(int n)
{
	if (n < 0)
		return -1;
	if ((n==0)||(n==1))
		return 1;
	return n*Factorial2(n-2);
}

int Binomial(int n, int k)
{
	if ((n<0)||(k<0))
		return -1;
	return Factorial(n)/(Factorial(k)*Factorial(n-k));
} 

double Stirling(int n)
{
	if (n < 0)
		return -1;
	if ((n==0)||(n==1))
		return 1;
	return sqrt(2*3.1415927*n)*exp(n*log(n)-n);
}

int Fibonacci(int n)
{
	if (n < 1)
		return -1;

	if ((n == 1)||(n == 2))
		return 1;

	int a, b, c, i;
	
	a = 1;
	b = 1;
	
	for (i = 3; i <= n; i++)
	{
		c = a + b;
		a = b;
		b = c;
	}
	
	return b;

int PrimeQ(int n)
{
	if (n < 2)
		return 0;
	int i, s;

	s = round(sqrt(n)) + 1;
	
	for (i = 2; i <= s; i++)
		if (n % i == 0)
			return 0;
	return 1; 
}

int Prime(int n)
{
	if (n < 1)
		return -1;

	int *array;
	int i, j, k;

	array = malloc(sizeof(int) * n * n);

	for (i = 0; i < n*n; i++)
		array[i] = 1;

	for (i = 2, k = 1; k <= n; i++)
		if (array[i] != 0)
		{
			k++;
			for (j = 2*i; j < n*n; j += i)
				array[j] = 0;
		}

	return i - 1;
}

int PowerMod(long a, long n, long m)
{
	if (n == 1)
		return a % m;
	int b;
	if (n % 2 == 0) {
		b = PowerMod(a, n/2, m);
		return b*b % m;
	} else {
		return a * PowerMod(a, n-1, m) % m;
	}
}

int DiscreteLog(long a, long b, long m)
{
	int c = a;
	int n = 1;
	while(c != b)
	{
		c = c*a % m;
		n++;
	}
	return n;
}

int Inverse(long a, long m)
{

	int quotient, i, j, k;
	int oldr = a;
	int olds = 1;
	int oldt = 0;
	int r = m;
	int s = 0;
	int t = 1;	
	while (r != 0)
	{
		quotient = oldr / r;
		i = r;
		j = s;
		k = t;
		r = oldr - quotient * i;
		s = olds - quotient * j;
		t = oldt - quotient * k;
		oldr = i;
		olds = j;
		oldt = k;
	}
    return olds % m;
}

long* FactorInteger(long integer)
{
	long d, i, j, n, p, s;
	long *divisors;

	n = integer;
	s = integer;
	
	divisors = malloc(sizeof(long) * 200);

	for (i = 2, j = 0; i <= s; i++) 
		if (n % i == 0) 
		{
			p = i;
			d = 0;
			do {
				n /= p;
				d += 1;
			} while (n % p == 0);
			divisors[j++] = p;
			divisors[j++] = d;
		}
	divisors[j] = 0;
	return divisors;
}


static PyObject* c_factorial(PyObject* self, PyObject* args)
{
	int n;

	if (!PyArg_ParseTuple(args, "i", &n))
		return NULL;

	return Py_BuildValue("i", Factorial(n));
}

static PyObject* c_factorial2(PyObject* self, PyObject* args)
{
	int n;

	if (!PyArg_ParseTuple(args, "i", &n))
		return NULL;

	return Py_BuildValue("i", Factorial2(n));
}

static PyObject* c_binomial(PyObject* self, PyObject* args)
{
	int n, k;

	if (!PyArg_ParseTuple(args, "ii", &n, &k))
		return NULL;

	return Py_BuildValue("i", Binomial(n, k));
}

static PyObject* c_stirling(PyObject* self, PyObject* args)
{
	int n; /*Объявление переменной*/

	if (!PyArg_ParseTuple(args, "i", &n))
		return NULL;

	return Py_BuildValue("d", Stirling(n));
}

static PyObject* c_fibonacci(PyObject* self, PyObject* args)
{
	int n;

	if (!PyArg_ParseTuple(args, "i", &n))
		return NULL;

	return Py_BuildValue("i", Fibonacci(n));
}

static PyObject* c_is_prime(PyObject* self, PyObject* args)
{
	int n;

	if (!PyArg_ParseTuple(args, "i", &n))
		return NULL;

	return Py_BuildValue("O", PrimeQ(n) ? Py_True : Py_False);
}

static PyObject* c_prime(PyObject* self, PyObject* args)
{
	int n;

	if (!PyArg_ParseTuple(args, "i", &n))
		return NULL;

	return Py_BuildValue("i", Prime(n));
}

static PyObject* c_power_mod(PyObject* self, PyObject* args)
{
	long a, n, m;

	if (!PyArg_ParseTuple(args, "iii", &a, &n, &m))
		return NULL;

	return Py_BuildValue("i", PowerMod(a, n, m));
}

static PyObject* c_discrete_log(PyObject* self, PyObject* args)
{
	long a, b, m;

	if (!PyArg_ParseTuple(args, "iii", &a, &b, &m))
		return NULL;

	return Py_BuildValue("i", DiscreteLog(a, b, m));
}

static PyObject* c_inverse(PyObject* self, PyObject* args)
{
	long a, m;

	if (!PyArg_ParseTuple(args, "ii", &a, &m))
		return NULL;

	return Py_BuildValue("i", Inverse(a, m));
}

static PyObject* c_factor_integer(PyObject* self, PyObject* args)
{
	long n;
	long *d;

	if (!PyArg_ParseTuple(args, "i", &n))
		return NULL;

	d = FactorInteger(n);

	int i, l;

	for (l = 0; d[l]; l++)
		{}

	PyObject* p = PyList_New(l);

	for (i = 0; i < l; i++)
		PyList_SetItem(p, i, PyLong_FromLong(d[i]));

	return p; /*Возвращаем результат*/
}

static PyMethodDef dpyth_methods[] = { /*Методы модуля*/
	{"c_factorial",      c_factorial,      METH_VARARGS, "Возвращает факториал числа n" },
	{"c_factorial2",     c_factorial2,     METH_VARARGS, "Возвращает двойной факториал числа n" },
	{"c_binomial",       c_binomial,       METH_VARARGS, "Возвращает число сочетаний из n по k" },
	{"c_stirling",       c_stirling,       METH_VARARGS, "Возвращает приближение факториала числа n по формуле Стирлинга"},
	{"c_fibonacci",      c_fibonacci,      METH_VARARGS, "Возвращает n-ый элемент последовательности Фибоначчи"},
	{"c_is_prime",       c_is_prime,       METH_VARARGS, "Проверяет, является ли число простым"},
	{"c_prime",          c_prime,          METH_VARARGS, "Возвращает n-ое простое число"},
	{"c_power_mod",      c_power_mod,      METH_VARARGS, "Возводит число в степень в кольце вычетов"},
	{"c_discrete_log",   c_discrete_log,   METH_VARARGS, "Логарифмирование в кольце вычетов"},
	{"c_inverse",        c_inverse,        METH_VARARGS, "Возвращает обратный элемент в кольце вычетов"},
	{"c_factor_integer", c_factor_integer, METH_VARARGS, "Возвращает каноническое разложение числа в формате [простой делитель, степень делителя, ...]"},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef dpyth_module = {
	PyModuleDef_HEAD_INIT,
	"dpyth",
	"Функции для решения комбинаторных задач", 
	-1,
	dpyth_methods
};

PyMODINIT_FUNC PyInit_dpyth(void)
{
    return PyModule_Create(&dpyth_module);
}

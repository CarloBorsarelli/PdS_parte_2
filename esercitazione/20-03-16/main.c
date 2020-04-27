/*
16-03-2020

da compilare con GCC Linux senza librerie di runtime
-nostdlib

NON FUNZIONA
*/

void _start(){
	_IO_underflow_t *stdout = (_IO_underflow_t *) &_IO_2_1_stdout_;
	va_list arg;
	int done;
	
	va_start (arg, format);
	done = __vfprintf_internal (stdout, "Hello SysProg!\n", arg, 0);
  	va_end (arg);

	return;
}
void fib(int x, int y) {
	if(x == 1) {
		y += 1;
	} else {
		y += 1;
		fib(x-1, y);
		printf("fib is %d\n",y);
	}
}

void main(){
	int y;
	y = 0;
	fib(10,y);
}

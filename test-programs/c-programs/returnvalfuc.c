int num(int a){ 
	return a;
}

int func(int n){ 
	int sum;
	sum = 0;
	for(int i=1;i<=n;i++) {
		sum += num(i);
	}
	return sum;
}

void main(){
	int n, ans;
	n = 50; 
	ans = func(n);
	printf("ans is %d\n",ans);
}

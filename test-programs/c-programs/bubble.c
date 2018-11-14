int inp[100];
void initialize(int n){
	int i;
	for(int i=0;i<n;i++) {
		inp[i] = n - i;
	}

	for(int i=0;i<n;i++) {
		printf("%d ",inp[i]);
	}
	printf("\n");
}


void bubblesort(int n){
	int i;
	int tmp;
	for(int i=0;i<n;i++) {
		for(int j=0;i<n-i-1;j++) {
			if(inp[j] > inp[j+1]){
				tmp = inp[j];
				inp[j] = inp[j+1];
				inp[j+1] = tmp;
			}
		}
	}

	for(int i=0;i<n;i++) {
		printf("%d ",inp[i]);
	}
	printf("\n");
}

void main() {
	int n;
	n = 10;
	initialize(n);
	bubblesort(n);
}

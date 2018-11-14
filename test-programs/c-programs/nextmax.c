int arr[100];
void initialize(int n){
	int i;
	for(int i=0;i<n;i++) {
		arr[i] = n - i;
	}

	for(int i=0;i<n;i++) {
		printf("%d ",arr[i]);
	}
	printf("\n");
}

void nextMax(int n){
	int max1, max2;
	if(n<2){
		printf("Invalid Input");
	}
	max1 = -1;
	max2 = -1;
	for(int i=0;i<n;i++) {
		if(arr[i] > max1){
			max2 = max1;
			max1 = arr[i];
		}
		else{
			if(arr[i] > max2){ 
				if(arr[i] != max1){
					max2 = arr[i];
				}
			}
		}
	}

	if(max2 == -1) {
		printf("No second largest element");
	}
	else{
		printf("Second Largest element is %d",max2);
	}
}

void main(){
	int n;
	n = 100;
	initialize(n);
	nextMax(n);
}

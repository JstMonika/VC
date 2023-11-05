#include<stdio.h>

int main(){
	
	int arr[1010];
	
	for(int i=0;i<1010;i++){
		arr[i] = 0;
	}
	
	int N,L;
	
	scanf("%d %d",&N,&L);
	
	for(int i=0;i<N;i++){
		scanf("%d",&arr[i]);
	}

	int bed = 0;
	
	for(int i=0;i<N;i++){
		int flag2 = 0;
		for(int j=0;j<L-2;j++){
			if(arr[i]<arr[j+i+1] && arr[j+i+1]>arr[L+i-1] && (L+i-1)<N){
				flag2++;
			}
		}
		if(L%2==0){
			if(flag2==(L/2-1)*2){
				for(int j=0;j<L;j++){
				printf("%d",arr[j+i]);
				if(j<L-1){
					printf(" ");
				}else{
					printf("\n");
				}
			}
			bed++;
			}
		}else{
			if(flag2==(2*(L/2-1)+1)){
				for(int j=0;j<L;j++){
				printf("%d",arr[j+i]);
				if(j<L-1){
					printf(" ");
				}else{
					printf("\n");
				}
			}
			bed++;
			}
		}
	}
	
	if(bed==0){
		printf("Domo\n");
	}
	
	
	return 0;
}
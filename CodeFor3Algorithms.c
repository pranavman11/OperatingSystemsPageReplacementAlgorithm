#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

void lrureplacement(int* refstr,int n,int frames);
void fifo(int* refstr,int n,int frames);
void optimalRep(int* refstr,int n,int frames);

int main(int argc, char const *argv[]) {
	if(argc < 2) {
		printf("Enter valid input\n");
		return 1;
	}
	else {
		printf("%s Opened as input file\n", argv[1]);
	}

	freopen(argv[1], "r", stdin);
	int n, i;
	scanf("%d", &n);
	int *refstr = (int *) malloc(sizeof(int) * n);

	for(i = 0; i < n; ++i) {
		scanf("%d", &refstr[i]);
	}

	int frames;
	scanf("%d", &frames);

	if(argc == 2) {
		fifo(refstr,n,frames);
		lrureplacement(refstr,n,frames);
		optimalRep(refstr,n,frames);
	}
	else {
		for(i = 2; i < argc; ++i) {
			if(argv[i][0] == 'f') {
				fifo(refstr,n,frames);
			}
			else if(argv[i][0] == 'l') {
				lrureplacement(refstr,n,frames);
			}
			else {
				optimalRep(refstr,n,frames);
			}
		}
	}
	return 0;
}
void lrureplacement(int* refstr,int n,int frames){
	printf("----Least Recently Used----\n");
	int arr[frames],search[frames],min[frames];
	int nnn=0,minn,ans;
	int no =frames;
	int ind;
	int faults = 0,hits = 0;
	for(int i=0;i<frames;i++){
		arr[i] = 9999;
	}

	for(int j=0;j<n;j++){
		int this = 0;
		int dont = 0;
		for(int i=0;i<frames;i++){
			//for array is empty
			if(arr[i]==9999){
				arr[i] = refstr[j];
				//break;
				this =1;
				faults++;
				//printf("Added |%d|\n", arr[i]);
				break;
			}
			//printf("Array %d\n", arr[i]);
		}
		if(this == 0){
			for(int i=0;i<frames;i++){
				if(refstr[j] == arr[i]){
					dont = 1;
					hits++;
				}
			}
			if(dont==0){
				for(int k=0;k<frames;k++){
					//printf("%d\n", arr[k]);
					search[k] = arr[k];
					min[k] = 0;
				}
			
				for(int i=0;i<frames;i++){
					for(int k=j-1;k>=0;k--){
						if(search[i] == refstr[k]){
							//save the index
							search[i] = k;
							break;
						}
					}
				}
				minn = 9999;
				ans = 1000;
				for(int i=0;i<frames;i++){
					if(search[i] < minn){
						minn = search[i];
						ans = i;
					}
				}
				arr[ans] = refstr[j];
				faults++;
			}
		}
		printf("Refernce string element %d\n",refstr[j] );
		for(int i=0;i<frames;i++){
			if(arr[i] == 9999){
				printf("| |\n");
			}
			else{
				printf("|%d|\n", arr[i]);
			}
		}
	}
	printf("Faults-%d Hits-%d\n", faults,hits);
	for(int i=0;i<frames;i++){
		printf("Final |%d|\n",arr[i] );
	}
}

//First-In-First-Out
void fifo(int* refstr,int n,int frames){
	printf("----First-In-First-Out Replacement----\n");
	int ans = 0;
	int faults=0,hits=0;
	int arr[frames];
	for(int i=0;i<frames;i++){
		arr[i] = 9999;
	}
	for(int j=0;j<n;j++){
		int this = 0;
		int dont = 0;
		for(int i=0;i<frames;i++){
			//for array is empty
			if(arr[i]==9999){
				arr[i] = refstr[j];
				//break;
				this =1;
				faults++;
				//printf("Added |%d|\n", arr[i]);
				break;
			}
			//printf("Array %d\n", arr[i]);
		}
		//doing nothing
		if(this == 0){
			for(int i=0;i<frames;i++){
				if(refstr[j] == arr[i]){
					dont = 1;
					hits++;
				}
			}
			if(dont==0){
				arr[ans] = refstr[j];
				ans++;
				if(ans >= frames){
					ans = 0;
				}
				faults++;
			}
		}
		printf("Refernce string element %d\n",refstr[j] );
		for(int i=0;i<frames;i++){
			if(arr[i] == 9999){
				printf("| |\n");
			}
			else{
				printf("|%d|\n", arr[i]);
			}
		}
	}
	printf("Faults-%d Hits-%d\n", faults,hits);
	for(int i=0;i<frames;i++){
		printf("Final |%d|\n",arr[i] );
	}

	return;
}

//Optimal replacement
void optimalRep(int* refstr,int n,int frames){
	printf("----Optimal Replacement----\n");
	int arr[frames],search[frames],min[frames];
	int nnn=0,maxx,ans;
	int no =frames;
	int ind;
	int faults = 0,hits = 0;
	for(int i=0;i<frames;i++){
		arr[i] = 9999;
	}

	for(int j=0;j<n;j++){
		int this = 0;
		int dont = 0;
		int noo = 0;
		for(int i=0;i<frames;i++){
			//for array is empty
			if(arr[i]==9999){
				arr[i] = refstr[j];
				//break;
				this =1;
				faults++;
				//printf("Added |%d|\n", arr[i]);
				break;
			}
			//printf("Array %d\n", arr[i]);
		}
		if(this == 0){
			for(int i=0;i<frames;i++){
				if(refstr[j] == arr[i]){
					dont = 1;
					hits++;
				}
			}
			if(dont==0){
				for(int k=0;k<frames;k++){
					//printf("%d\n", arr[k]);
					search[k] = arr[k];
					min[k] = 0;
				}
			
				for(int i=0;i<frames;i++){
					int found =0;
					for(int k=j+1;k<n;k++){
						if(search[i] == refstr[k]){
							//save the index
							search[i] = k;
							found = 1;
							break;
						}

					}
					if(found == 0){
						search[i] = -9999999;
						//if search contains -9999999 then different operation
						noo = 1;
					}
				}
				
				if(noo == 1){
					for(int i=0;i<frames;i++){
						if(search[i] == -9999999){
							ans = i;
							break;
						}
					}
					//printf("Maxx %d ans %d\n",maxx,ans);
					arr[ans] = refstr[j];
					faults++;

				}
				else{
					maxx = -9999;
					ans = 1000;
					for(int i=0;i<frames;i++){
						if(search[i] > maxx){
							maxx = search[i];
							ans = i;
						}
					}
					//printf("Maxx %d ans %d\n",maxx,ans);
					arr[ans] = refstr[j];
					faults++;
				}
			}
		}
		printf("Refernce string element %d\n",refstr[j] );
		for(int i=0;i<frames;i++){
			if(arr[i] == 9999){
				printf("| |\n");
			}
			else{
				printf("|%d|\n", arr[i]);
			}
		}
	}
	printf("Faults-%d Hits-%d\n", faults,hits);
	for(int i=0;i<frames;i++){
		printf("Final |%d|\n",arr[i] );
	}
}
/*OUTPUT
p9.txt Opened as input file
----First-In-First-Out Replacement----
Refernce string element 1
|1|
| |
| |
| |
Refernce string element 2
|1|
|2|
| |
| |
Refernce string element 3
|1|
|2|
|3|
| |
Refernce string element 4
|1|
|2|
|3|
|4|
Refernce string element 1
|1|
|2|
|3|
|4|
Refernce string element 2
|1|
|2|
|3|
|4|
Refernce string element 5
|5|
|2|
|3|
|4|
Refernce string element 1
|5|
|1|
|3|
|4|
Refernce string element 2
|5|
|1|
|2|
|4|
Refernce string element 3
|5|
|1|
|2|
|3|
Refernce string element 4
|4|
|1|
|2|
|3|
Refernce string element 5
|4|
|5|
|2|
|3|
Faults-10 Hits-2
Final |4|
Final |5|
Final |2|
Final |3|
----Least Recently Used----
Refernce string element 1
|1|
| |
| |
| |
Refernce string element 2
|1|
|2|
| |
| |
Refernce string element 3
|1|
|2|
|3|
| |
Refernce string element 4
|1|
|2|
|3|
|4|
Refernce string element 1
|1|
|2|
|3|
|4|
Refernce string element 2
|1|
|2|
|3|
|4|
Refernce string element 5
|1|
|2|
|5|
|4|
Refernce string element 1
|1|
|2|
|5|
|4|
Refernce string element 2
|1|
|2|
|5|
|4|
Refernce string element 3
|1|
|2|
|5|
|3|
Refernce string element 4
|1|
|2|
|4|
|3|
Refernce string element 5
|5|
|2|
|4|
|3|
Faults-8 Hits-4
Final |5|
Final |2|
Final |4|
Final |3|
----Optimal Replacement----
Refernce string element 1
|1|
| |
| |
| |
Refernce string element 2
|1|
|2|
| |
| |
Refernce string element 3
|1|
|2|
|3|
| |
Refernce string element 4
|1|
|2|
|3|
|4|
Refernce string element 1
|1|
|2|
|3|
|4|
Refernce string element 2
|1|
|2|
|3|
|4|
Refernce string element 5
|1|
|2|
|3|
|5|
Refernce string element 1
|1|
|2|
|3|
|5|
Refernce string element 2
|1|
|2|
|3|
|5|
Refernce string element 3
|1|
|2|
|3|
|5|
Refernce string element 4
|4|
|2|
|3|
|5|
Refernce string element 5
|4|
|2|
|3|
|5|
Faults-6 Hits-6
Final |4|
Final |2|
Final |3|
Final |5|
*/

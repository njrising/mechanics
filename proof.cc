#include <iostream>
#include <array>
#include <algorithm>

//#include <chrono>
#include <cstdio>

// kronecker delta 
int k_delta(int i, int j){
	if(i == j){return 1;}
	else{return 0;}	
}

// permutation tensor
int epsilon(std::array<int,3> &v,int n=0){
	if(v[0] == v[1] || v[0] == v[2] || v[1] == v[2]){return 0;}
	else{
		std::stable_sort(v.begin(),v.end(),[&n](int a,int b){n+=(a<b);return a<b;});
		return (n % 2 == 0) ? 1 : -1;
	}
}
// faster permutation tensor
int epsilon_(int i,int j,int k){
	if(i == j || i == k || j == k){return 0;}
	else if(i==1 && j==2 && k==3){return 1;}
	else if(i==2 && j==3 && k==1){return 1;}
	else if(i==3 && j==1 && k==2){return 1;}
	else if(i==3 && j==2 && k==1){return -1;}
	else if(i==1 && j==3 && k==2){return -1;}
	else if(i==2 && j==1 && k==3){return -1;}
}


int main(){

	//std::array<int,3> arr = {3,2,1};
	
//	auto start = std::chrono::high_resolution_clock::now();
	
//	for(int i = 0;i<1000000;++i){
//		epsilon_(3,2,1);
//	}
//	auto finish = std::chrono::high_resolution_clock::now();
//	std::chrono::duration<double> elapsed = finish - start;
//	std::cout<<"Elapsed time: "<<elapsed.count()<<"s\n";
	
	int epsilon_result[81] = {};
	int delta_result[81] = {};
	int index[81][4] = {};
	
	int count = -1;
	uint8_t i,j,k,l,m;
	i=j=k=l=m=1;
	for(i = 1;i < 4;++i){
		for(j = 1;j < 4;++j){
			for(k = 1;k < 4;++k){
				for(l = 1;l < 4;++l){
					count++;
					for(m=1;m < 4;++m){
						//index[count][0] = i;index[count][1] = j;index[count][2] = k;index[count][3] = l;
						epsilon_result[count] += epsilon_(i,j,m) * epsilon_(k,l,m); 
					}
					delta_result[count] = k_delta(i,k) * k_delta(j,l) - k_delta(i,l) * k_delta(j,k);
				}
			}
		}
	}
	
	for(int i=0;i<81;++i){
		std::cout<<epsilon_result[i]<<' '<<delta_result[i]<<'\n';
	}
	
	
	

	return 0;
}
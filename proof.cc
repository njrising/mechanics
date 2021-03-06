#include <iostream>  // output
#include <array>     // array
#include <algorithm> // stable_sort
// Proof of a formula found in advanced mechanics textbooks
// The following equation is actually a set of 81 eqautions
// e_ijm * e_klm = d_ik * d_jl - d_il * d_jk
// Preferring a computational approach to verifying the relationship,
// We can show the relationship is true through brute computation.
//
// Author: Nathan Rising
// 
// I considered different methods to writing the epsilon function
// first through sorting and lambdas, however a simpler approach 
// uses only if statements and is considerably more efficient

// kronecker delta 
std::uint8_t k_delta(int i, int j){
	if(i == j){return 1;}
	else{return 0;}	
}

// permutation tensor
int epsilon(int i,int j,int k,int n=0){
	if(i == j || i == k || j == k){return 0;}
	else{
		std::array<int,3> v = {i,j,k};
		std::stable_sort(v.begin(),v.end(),[&n](int a,int b){n+=(a<b);return a<b;});
		return (n % 2 == 0) ? 1 : -1;
	}
}
// faster permutation tensor
std::int8_t epsilon_(int i,int j,int k){
	if(i == j || i == k || j == k){return 0;}
	else if(i==1 && j==2 && k==3){return 1;}
	else if(i==2 && j==3 && k==1){return 1;}
	else if(i==3 && j==1 && k==2){return 1;}
	else if(i==3 && j==2 && k==1){return -1;}
	else if(i==1 && j==3 && k==2){return -1;}
	else if(i==2 && j==1 && k==3){return -1;}
}

int main(){
	std::int16_t epsilon_result[81] = {};  // epsilon values
	std::int16_t delta_result[81] = {};    // delta values
	std::int8_t count = -1;				  	
	std::uint8_t i,j,k,l,m;
	i=j=k=l=m=1;
	// looping through...
	for(i = 1;i < 4;++i){
		for(j = 1;j < 4;++j){
			for(k = 1;k < 4;++k){
				for(l = 1;l < 4;++l){
					count++;
					for(m = 1;m < 4;++m){
						epsilon_result[count] += epsilon_(i,j,m) * epsilon_(k,l,m); 
					}
					delta_result[count] = k_delta(i,k) * k_delta(j,l) - k_delta(i,l) * k_delta(j,k);
				}
			}
		}
	}
	// print results.
	for(i=0;i<81;++i){
		std::cout<<epsilon_result[i]<<' '<<delta_result[i]<<'\n';
	}
	return 0;
}
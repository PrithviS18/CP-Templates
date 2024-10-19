void primeFactors(int n) 
{ 
    if (n%2==0)vec.push_back(2);
    while (n % 2 == 0) {  
        n = n/2; 
    }  
    for (int i = 3; i <= sqrt(n); i = i + 2) { 
        if (n%i==0)vec.push_back(i);
        while (n % i == 0){ 
            n = n/i; 
        } 
    } 
    if (n > 2)vec.push_back(i);
} 

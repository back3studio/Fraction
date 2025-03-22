#include <iostream>
#include <algorithm>

class Fraction{
private:
    long long num;
    long long den;
public:
    Fraction(): num(0),den(1) {};
//    Fraction(const int a,const int b): num(a),den(b) {};
	Fraction(const long long a): num(a),den(1) {cancel();};
    Fraction(const long long a,const long long b): num(a),den(b) {cancel();};
	Fraction(const std::string s){
		long long t=0;
		bool f=1;
		try{
			for(auto m : s){
				if(m=='/'){
					set_numerator(t);
					t=0;
					f=0;
				}else if(m<'0'||m>'9'){
					throw std::invalid_argument("Unsupported input!");
				}else{
					t=t*10+m-'0';
				}
			}
		}catch (const std::invalid_argument& e) {
			std::cerr << "Error: " << e.what();
			exit(-1);
		}
		if(f){
			set_numerator(t);	
		}else{
			set_denominator(t);
		}
		cancel();
	}
	
	operator double(){
		return 1.0d*num/den;
	}
	
	void set_numerator(long long x){
		num=x;
	}
	void set_denominator(long long x){
		den=x;
	}
    long long numerator(){
        return num;
    }
    long long denominator(){
        return den;
    }
	
	void cancel(){
		long long g=std::__gcd(num,den);
		num/=g;
		den/=g;
	}
	
	friend std::istream& operator>> (std::istream& i, const Fraction& fra);
	friend std::ostream& operator<< (std::ostream& o, const Fraction& fra);
};

Fraction operator+(Fraction& a,Fraction& b){
	long long an=a.numerator(),ad=a.denominator(),bn=b.numerator(),bd=b.denominator(),d;
	d=ad*bd/std::__gcd(ad,bd);
	an*=d/ad,bn*=d/bd;
	Fraction tmp(an+bn,d);
	return tmp;
}
Fraction operator-(Fraction& a,Fraction& b){
	long long an=a.numerator(),ad=a.denominator(),bn=b.numerator(),bd=b.denominator(),d;
	d=ad*bd/std::__gcd(ad,bd);
	an*=d/ad,bn*=d/bd;
	Fraction tmp(an-bn,d);
	return tmp;
}
Fraction operator*(Fraction& a,Fraction& b){
	Fraction tmp(a.numerator()*b.numerator(),a.denominator()*b.denominator());
	tmp.cancel();
	return tmp;
}
Fraction operator/(Fraction& a,Fraction& b){
	try{
		if(a.denominator()*b.numerator()==0){
			throw std::invalid_argument("Devide by zero!");
		}
	}catch(const std::invalid_argument& e){
		std::cerr << "Error:" << e.what();
		exit(-1);
	}
	Fraction tmp(a.numerator()*b.denominator(),a.denominator()*b.numerator());
	tmp.cancel();
	return tmp;
}

std::istream& operator>> (std::istream& i, Fraction& fra){
	std::string s;
	i >> s;
	fra = Fraction(s);
	return i;
}

std::ostream& operator<< (std::ostream& o, const Fraction& fra)
{
	if(fra.num==0 || fra.den==1) o << fra.num;
	else o << fra.num << '/' << fra.den;
	return o;
}

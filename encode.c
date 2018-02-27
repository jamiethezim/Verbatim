#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int getwordlen(char * s){
	// while the number of bits % 3 != 0
	// tack more zeros onto the front
	char* p = s;
	while (*p != '\0'){
		p++;
	}
	return (p-s);
}

long long change_format(char* s){
	int wordlen = getwordlen(s);
	if (wordlen > 8){
		fprintf(stderr, "Error: %s has length greater than 8, please supply word where length less than or equal to 8\n", s);
		exit(1);
	}

	long long new_s = 0;
	long long shift_by = 0;
	for (int i = 0; i < wordlen; i++){
		new_s |= ((long long) s[i]) << shift_by;
		shift_by += 8; //16, 24, 32, etc.
	}
	return new_s;
}

unsigned char * getencodingscheme(){
	// Stub function
	/// TODO get argv from main, and parse into scheme, so that the key is secret!
	// for now, just use a static scheme
	unsigned char *scheme;
	scheme = malloc(8 * sizeof(unsigned char));
	scheme[0] = 'v';
	scheme[1] = 'e';
	scheme[2] = 'r';
	scheme[3] = 'b';
	scheme[4] = 'a';
	scheme[5] = 't';
	scheme[6] = 'i';
	scheme[7] = 'm';
	
	return scheme;
};


void translate(char final_word[23], unsigned char* scheme, long long word, int wordlength){
	long long three_bit_mask = 0xd000000000000000; // three bits in the 61st-63rd bit
	//char final_word[23] = {'\0'}; // a word of length 8 will have 64 bits, which will get encoded to ceil(64/3) = 22 letters
	for (int i = 0; i < wordlength; i++){
		int letter = (int) (word & three_bit_mask) >> ((64-3)-i*3);
		final_word[i] = scheme[letter];
		three_bit_mask = three_bit_mask >> 3;
	}
	

}

/*
unsigned char* fresh_encode(unsigned char * this_word){
	return "ok";
}

int test(){
	fprintf(stderr, "****** TESTING 3 cases **********\n");
	// 106, 97, 109, 105, 101 -> 1101010, 1100001, 1101101, 1101001, 1100101 ->
	// encode(11010101100001110110111010011100101) -> brtaeiimrbat
	assert(fresh_encode("jamie") == "brtaeiimrbat"); 
	assert(fresh_encode("5!") == "vbriaae"); //53, 33 -> 00110101, 00100001 -> encode(000011010100100001) -> vbriaae
	assert(fresh_encode("||") == "vmiema"); // 124, 124 -> 1111100, 1111100 -> encode(000111110001111100) -> vmiema
	fprintf(stderr, "*Done with test cases... add some more?\n");

}
*/
int main(int argc, char* argv[]){
	char* t = argv[1];
	long long test = change_format(t);
	fprintf(stdout, "new word is %llu\n", test);

	//test() //uncomment to run unit tests
	//encode_file() // Uncomment when ready to encode a story!
}	

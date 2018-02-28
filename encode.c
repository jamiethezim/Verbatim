#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int getwordlen(unsigned char * s){
	// while the number of bits % 3 != 0
	// tack more zeros onto the front
	unsigned char* p = s;
	while (*p != '\0'){
		p++;
	}
	return (p-s);
}

long long change_format(unsigned char* s){
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


void translate(unsigned char final_word[23], unsigned char* scheme, long long word, int wordlength){
	long long three_bit_mask = 0xd000000000000000; // three bits in the 61st-63rd bit
	//char final_word[23] = {'\0'}; // a word of length 8 will have 64 bits, which will get encoded to ceil(64/3) = 22 letters

	if (wordlength == 8){

	}
		// we have a special case where all 64 bits are used to represent the word
		// but we need two extra bits at the front to be able to interpret the bits three-by-three (66 % 3 = 0)
		// so now we have to handle this very carefully
		// read the last 63 bits backwards to get them into translated/encoded chars
		// then for the 64th bit, create a new temp char that has two zeros in front of the 64th bit
		// stuff that temp char to the front of the encoded word
	int i = 0; 
	while (i < wordlength*8/3){
		int letter = (int) (word & three_bit_mask) >> ((64-3)-i*3);
		final_word[i] = scheme[letter];
		three_bit_mask = three_bit_mask >> 3;
		i += 3;
	}

}


int test(){
	unsigned char* schema;
	schema = getencodingscheme();
	fprintf(stderr, "****** TESTING 3 cases **********\n");
	// 106, 97, 109, 105, 101 -> 1101010, 1100001, 1101101, 1101001, 1100101 ->
	// encode(11010101100001110110111010011100101) -> brtaeiimrbat
	unsigned char* new_word = (unsigned char *) malloc(sizeof(unsigned char) * 23);
	long long formatted = 0;

	// test 1
	formatted = change_format("jamie\0");
	translate(new_word, schema, formatted, 5);
 	assert(new_word == "brtaeiimrbat"); 

 	// test 2
 	formatted = change_format("5!\0");
 	translate(new_word, schema, formatted, 2);
	assert(new_word == "vbriaae"); //53, 33 -> 00110101, 00100001 -> encode(000011010100100001) -> vbriaae

	// test 3
	formatted = change_format("||\0");
	translate(new_word, schema, formatted, 2);
	assert(fresh_encode("||") == "vmiema"); // 124, 124 -> 1111100, 1111100 -> encode(000111110001111100) -> vmiema

	fprintf(stderr, "*Done with test cases... add some more?\n");

	return 0;
}

int main(int argc, char* argv[]){
	char* t = argv[1];
	long long baby = change_format(t);
	fprintf(stdout, "new word is %llu\n", baby);

	test(); //uncomment to run unit tests
	//encode_file() // Uncomment when ready to encode a story!
}	

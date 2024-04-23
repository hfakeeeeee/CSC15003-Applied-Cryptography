#include "Table.h"
#include "Header.h"

// Function to convert a number in Decimal to Binary
string convertDecimalToBinary(int decimal) {
	string binary;

	while (decimal != 0) {
		binary = (decimal % 2 == 0 ? "0" : "1") + binary;
		decimal = decimal / 2;
	}

	while (binary.length() < 4) {
		binary = "0" + binary;
	}

	return binary;
}

// Function to convert a number in Binary to Decimal
int convertBinaryToDecimal(string bin) {
	int decimal = 0;
	int counter = 0;
	int size = bin.length();

	for (int i = size - 1; i >= 0; i--) {
		if (bin[i] == '1') {
			decimal += pow(2, counter);
		}
		counter++;
	}

	return decimal;
}

//Function to convert a Text String to Binary String
string convertStringtoBinary(string str) {
	string binary = "";

	for (char const& c : str) {
		binary += bitset<8>(c).to_string();
	}
	return binary;
}

//Function to create a map for a 4-bit hex
void createMap(unordered_map<string, char>* um)
{
	(*um)["0000"] = '0';
	(*um)["0001"] = '1';
	(*um)["0010"] = '2';
	(*um)["0011"] = '3';
	(*um)["0100"] = '4';
	(*um)["0101"] = '5';
	(*um)["0110"] = '6';
	(*um)["0111"] = '7';
	(*um)["1000"] = '8';
	(*um)["1001"] = '9';
	(*um)["1010"] = 'A';
	(*um)["1011"] = 'B';
	(*um)["1100"] = 'C';
	(*um)["1101"] = 'D';
	(*um)["1110"] = 'E';
	(*um)["1111"] = 'F';
}

// Function to convert Binary string to Hexadecimal String (1)
string convertBinarytoHex1(string bin) {
	stringstream ss;
	bitset<8> byte;

	for (size_t i = 0; i < bin.size(); i += 8) {
		byte = bitset<8>(bin.substr(i, 8));
		ss << hex << setfill('0') << setw(2) << byte.to_ulong() << " ";
	}

	return ss.str();
}

// Function to convert Binary string to Hexadecimal String (2)
string convertBinarytoHex2(string bin) {
	int l = bin.size();
	int t = bin.find_first_of('.');

	// length of string before '.'
	int len_left = t != -1 ? t : l;

	// add min 0's in the beginning to make
	// left substring length divisible by 4
	for (int i = 1; i <= (4 - len_left % 4) % 4; i++)
		bin = '0' + bin;

	// if decimal point exists   
	if (t != -1) {
		// length of string after '.'
		int len_right = l - len_left - 1;

		// add min 0's in the end to make right
		// substring length divisible by 4
		for (int i = 1; i <= (4 - len_right % 4) % 4; i++)
			bin = bin + '0';
	}

	// create map between binary and its
	// equivalent hex code
	unordered_map<string, char> bin_hex_map;
	createMap(&bin_hex_map);

	int i = 0;
	string hex = "";

	while (1) {
		// one by one extract from left, substring
		// of size 4 and add its hex code
		hex += bin_hex_map[bin.substr(i, 4)];
		i += 4;
		if (i == bin.size())
			break;

		// if '.' is encountered add it to result
		if (bin.at(i) == '.')
		{
			hex += '.';
			i++;
		}
	}

	// required hexadecimal number
	return hex;
}

// Function to convert Hexadecimal string to Binary string
string convertHextoText(string hex) {
	string ascii = "";

	for (size_t i = 0; i < hex.length(); i += 2)
	{
		// extract two characters from hex string
		string part = hex.substr(i, 2);

		// change it into base 16 and
		// typecast as the character
		char ch = stoul(part, nullptr, 16);

		// add this char to final ASCII string
		ascii += ch;
	}

	return ascii;
}

string convertHextoBinary(string hexString) {
	string binaryString = "";

	for (size_t i = 0; i < hexString.length(); ++i) {
		char hexChar = hexString[i];
		int hexValue = 0;
		if (hexChar >= '0' && hexChar <= '9') {
			hexValue = hexChar - '0';
		}
		else if (hexChar >= 'A' && hexChar <= 'F') {
			hexValue = hexChar - 'A' + 10;
		}
		else if (hexChar >= 'a' && hexChar <= 'f') {
			hexValue = hexChar - 'a' + 10;
		}
		bitset<4> bits(hexValue);
		binaryString += bits.to_string();
	}

	return binaryString;
}

// Function to do a circular left shift by 1
string shift_left_once(string key_chunk) {
	string shifted = "";

	for (int i = 1; i < 28; i++) {
		shifted += key_chunk[i];
	}

	shifted += key_chunk[0];

	return shifted;
}

// Function to do a circular left shift by 2
string shift_left_twice(string key_chunk) {
	string shifted = "";

	for (int i = 0; i < 2; i++) {
		for (int j = 1; j < 28; j++) {
			shifted += key_chunk[j];
		}

		shifted += key_chunk[0];
		key_chunk = shifted;
		shifted = "";
	}

	return key_chunk;
}

string round_keys[16];

// Function to generate 16 keys
void generate_keys(string key) {
	// 1. Compressing the key using the PC1 table
	string perm_key = "";
	string key_temp[16];

	for (int i = 0; i < 56; i++) {
		perm_key += key[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(PC1[i]) - 1];
	}

	// 2. Dividing the result into two equal halves
	string left = perm_key.substr(0, 28);
	string right = perm_key.substr(28, 28);

	// Generating 16 keys
	for (int i = 0; i < 16; i++) {
		// 3.1. For rounds 1, 2, 9, 16 the key_chunks
		// are shifted by one.
		if (i == 0 || i == 1 || i == 8 || i == 15) {
			left = shift_left_once(left);
			right = shift_left_once(right);
		}

		// 3.2. For other rounds, the key_chunks
		// are shifted by two
		else {
			left = shift_left_twice(left);
			right = shift_left_twice(right);
		}

		// 4. The chunks are combined
		string combined_key = left + right;
		string round_key = "";

		// 5. Finally, the PC2 table is used to transpose
		// the key bits
		for (int i = 0; i < 48; i++) {
			round_key += combined_key[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(PC2[i]) - 1];
		}

		round_keys[i] = round_key;
		key_temp[i] = round_key;
		cout << "Key " << i + 1 << ":\t" << convertBinarytoHex1(key_temp[i]) << endl;
	}
}

// Function to compute xor between two strings
string Xor(string a, string b) {
	string result = "";
	int size = b.size();

	for (int i = 0; i < size; i++) {
		if (a[i] != b[i]) {
			result += "1";
		}
		else {
			result += "0";
		}
	}

	return result;
}

// Implementing the algorithm
string DES(string pt) {
	//1. Applying the initial permutation
	string perm = "";

	for (int i = 0; i < 64; i++) {
		perm += pt[(IP[i]) - 1];
	}

	// 2. Dividing the result into two equal halves 
	string left = perm.substr(0, 32);
	string right = perm.substr(32, 32);

	// The plain text is encrypted 16 times  
	for (int i = 0; i < 16; i++) {
		string right_expanded = "";

		// 3.1. The right half of the plain text is expanded
		for (int i = 0; i < 48; i++) {
			right_expanded += right[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(expansion_table[i]) - 1];
		};

		// 3.3. The result is xored with a key
		string xored = Xor(round_keys[i], right_expanded);
		string res = "";

		// 3.4. The result is divided into 8 equal parts and passed 
		// through 8 substitution boxes. After passing through a 
		// substituion box, each box is reduces from 6 to 4 bits.
		for (int i = 0; i < 8; i++) {
			// Finding row and column indices to lookup the
			// substituition box
			string row1 = xored.substr(i * 6, 1) + xored.substr(i * 6 + 5, 1);
			int row = convertBinaryToDecimal(row1);
			string col1 = xored.substr(i * 6 + 1, 1) + xored.substr(i * 6 + 2, 1) + xored.substr(i * 6 + 3, 1) + xored.substr(i * 6 + 4, 1);;
			int col = convertBinaryToDecimal(col1);
			int val = substition_boxes[i][row][col];
			res += convertDecimalToBinary(val);
		}

		// 3.5. Another permutation is applied
		string perm2 = "";

		for (int i = 0; i < 32; i++) {
			perm2 += res[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(permutation_table[i]) - 1];
		}

		// 3.6. The result is xored with the left half
		xored = Xor(perm2, left);

		// 3.7. The left and the right parts of the plain text are swapped 
		left = xored;
		if (i < 15) {
			string temp = right;
			right = xored;
			left = temp;
		}
	}

	// 4. The halves of the plain text are applied
	string combined_text = left + right;
	string ciphertext = "";

	// The inverse of the initial permuttaion is applied
	for (int i = 0; i < 64; i++) {
		ciphertext += combined_text[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(FP[i]) - 1];
	}

	//And we finally get the cipher text
	return ciphertext;
}

string decryption(string ct) {
	// Reversing the round_keys array for decryption
	int i = 15;
	int j = 0;

	while (i > j) {
		string temp = round_keys[i];
		round_keys[i] = round_keys[j];
		round_keys[j] = temp;
		i--;
		j++;
	}
	string decrypted = DES(ct);

	return decrypted;
}

string CBCRandomEnc(string m, string k) {
	// Convert message and key to binary
	string m_bin = convertStringtoBinary(m);
	string k_bin = convertStringtoBinary(k);

	// Generate round keys
	generate_keys(k_bin);

	// Use an all-zero IV
	string iv = string(8, 0);
	string iv_bin = convertStringtoBinary(iv);

	// Apply XOR on the message and the IV
	string m_iv_xor = Xor(m_bin, iv_bin);

	// Encrypt the message
	string c_bin = DES(m_iv_xor);

	// Convert encrypted message to hex
	string c_hex = c_bin;

	// Concatenate IV and encrypted message in hex format
	string c_iv_hex = iv_bin + c_hex;

	return c_iv_hex;
}

string CBCRandomDec(string c_iv_hex, string k) {
	// Convert the key to binary
	string k_bin = convertStringtoBinary(k);

	// Separate IV and encrypted message
	string iv = string(8, 0);
	string iv_bin = convertStringtoBinary(iv);

	string c_bin = c_iv_hex.substr(64, 64);

	// Decrypt the message
	string m_iv_xor_bin = decryption(c_bin);

	// XOR the decrypted message with the IV
	string m_bin = Xor(m_iv_xor_bin, iv_bin);

	// Convert the binary message back to text
	string m = m_bin;

	return m;
}
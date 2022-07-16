unsigned int abs_diff(unsigned int a, unsigned int b) {
	if (a > b) {
		return a - b;
	}
	return b - a;
}

unsigned int min(unsigned int a, unsigned int b) {
	if (a < b) {
		return a;
	}
	return b;
}

unsigned int gcd_binary_recursive(unsigned int a, unsigned int b) {
	if (a == 0) {
		return b;
	}
	if (b == 0) {
		return a;
	}
	if (a % 2 == 0) { // a is even
		if (b % 2 == 0) {
			return 2 * gcd_binary_recursive(a/2, b/2); // b is even
		}
		return gcd_binary_recursive(a/2, b); // b is odd
	}
	// a is odd
	if (b % 2 == 0) {
		return gcd_binary_recursive(a, b/2); // b is even
	}
	return gcd_binary_recursive(abs_diff(a, b), min(a, b)); // b is odd
}

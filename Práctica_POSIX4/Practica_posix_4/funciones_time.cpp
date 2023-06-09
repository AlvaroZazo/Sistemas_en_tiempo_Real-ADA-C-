#include "funciones_time.h"

struct timespec RestaTimeSpec(struct timespec src1, struct timespec src2) {
	struct timespec dst;
	if (src2.tv_nsec > src1.tv_nsec) {
		dst.tv_sec = src1.tv_sec - src2.tv_sec - 1;
		dst.tv_nsec = (src1.tv_nsec - src2.tv_nsec) + 1000000000;
	}
    else {
		dst.tv_sec = src1.tv_sec - src2.tv_sec;
		dst.tv_nsec = src1.tv_nsec - src2.tv_nsec;
    }
	return dst;
}

struct timespec SumaTimeSpec(struct timespec src1, struct timespec src2) {
	struct timespec dst;
	if (src2.tv_nsec + src1.tv_nsec > 1000000000) {
		dst.tv_sec = src1.tv_sec + src2.tv_sec + 1;
		dst.tv_nsec =  src2.tv_nsec + src1.tv_nsec - 1000000000;
	}
	else {
		dst.tv_nsec =  src2.tv_nsec + src1.tv_nsec;
		dst.tv_sec  = src1.tv_sec + src2.tv_sec;
	}
	return dst;
}

void AcumTimeSpec(struct timespec &dst, struct timespec src)
{
	if (dst.tv_nsec + src.tv_nsec > 1000000000) {
		dst.tv_sec = dst.tv_sec + src.tv_sec + 1;
		dst.tv_nsec =  dst.tv_nsec + src.tv_nsec - 1000000000;
	}
	else {
		dst.tv_nsec = dst.tv_nsec + src.tv_nsec;
		dst.tv_sec  = dst.tv_sec  + src.tv_sec;
	}
}

void ClearTimeSpec(struct timespec &dst) {
	dst.tv_sec = dst.tv_nsec = 0;
}

void ImprimirTimeSpec(struct timespec dst) {
	printf("Sec:  %ld\n", dst.tv_sec );
	printf("nSec: %09ld\n", dst.tv_nsec );
}

struct timespec segundos2timespec(double src) {
	struct timespec dst;
	dst.tv_sec=(int)src;
	dst.tv_nsec=(src-dst.tv_sec)*1000000000;
	while (dst.tv_nsec>999999999) {
		dst.tv_nsec-=1000000000;
		dst.tv_sec++;
	}
	return dst;
}

double timespec2segundos(struct timespec src) {
	return src.tv_sec+src.tv_nsec/1000000000.0;
}

struct timespec ms2timespec(int src) {
	struct timespec dst;
	dst.tv_sec=src/1000;
	dst.tv_nsec=(src%1000)*1000000;
	return dst;
}

int timespec2ms(struct timespec src) {
	return src.tv_sec*1000+src.tv_nsec/1000000;
}

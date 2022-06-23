#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_YEAR_DURATION	10	// 기간

// 구조체 선언
typedef struct {
	char	name[20];		// 이름
	char	sex;			// 성별 M or F
	int		freq[MAX_YEAR_DURATION]; // 연도별 빈도
} tName;

typedef struct {
	int		len;		// 배열에 저장된 이름의 수
	int		capacity;	// 배열의 용량 (배열에 저장 가능한 이름의 수)
	tName	*data;		// 이름 배열의 포인터
} tNames;

// 함수 원형 선언

// 연도별 입력 파일을 읽어 이름 정보(이름, 성별, 빈도)를 이름 구조체에 저장
// 이미 구조체에 존재하는(저장된) 이름은 해당 연도의 빈도만 저장
// 새로 등장한 이름은 구조체에 추가
// 주의사항: 동일 이름이 남/여 각각 사용될 수 있으므로, 이름과 성별을 구별해야 함
// 주의사항: 구조체 배열은 정렬 리스트(ordered list)이어야 함
// 이미 등장한 이름인지 검사하기 위해 bsearch 함수를 사용
// 새로운 이름을 저장할 메모리 공간을 확보하기 위해 memmove 함수를 이용하여 메모리에 저장된 내용을 복사
// names->capacity는 2배씩 증가
void load_names( FILE *fp, int year_index, tNames *names);

// 구조체 배열을 화면에 출력
void print_names( tNames *names, int num_year);

// bsearch를 위한 비교 함수
int compare( const void *n1, const void *n2);

// 이진탐색 함수
// return value: key가 발견되는 경우, 배열의 인덱스
//				key가 발견되지 않는 경우, key가 삽입되어야 할 배열의 인덱스
int binary_search( const void *key, const void *base, size_t nmemb, size_t size, int (*compare)(const void *, const void *));

// 함수 정의

// 이름 구조체 초기화
// len를 0으로, capacity를 1로 초기화
// return : 구조체 포인터
tNames *create_names(void)
{
	tNames *pnames = (tNames *)malloc( sizeof(tNames));
	
	pnames->len = 0;
	pnames->capacity = 1;
	pnames->data = (tName *)malloc(pnames->capacity * sizeof(tName));

	return pnames;
}

// 이름 구조체에 할당된 메모리를 해제
void destroy_names(tNames *pnames)
{
	free(pnames->data);
	pnames->len = 0;
	pnames->capacity = 0;

	free(pnames);
}
	
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	tNames *names;
	
	int num = 0;
	FILE *fp;
	int num_year = 0;
	
	if (argc == 1) return 0;

	// 이름 구조체 초기화
	names = create_names();

	// 첫 연도 알아내기 "yob2009.txt" -> 2009
	int start_year = atoi( &argv[1][3]);
	
	for (int i = 1; i < argc; i++)
	{
		num_year++;
		fp = fopen( argv[i], "r");
		assert( fp != NULL);
		
		int year = atoi( &argv[i][3]); // ex) "yob2009.txt" -> 2009
		
		fprintf( stderr, "Processing [%s]..\n", argv[i]);
		
		// 연도별 입력 파일(이름 정보)을 구조체에 저장
		load_names( fp, year-start_year, names);
		
		fclose( fp);
	}
	
	// 이름 구조체를 화면에 출력
	print_names( names, num_year);

	// 이름 구조체 해제
	destroy_names( names);
	
	return 1;
}

void load_names(FILE* fp, int year_index, tNames* names) {
	memset(names->data[0].freq, 0, sizeof(names->data[0].freq));

	do {
		char str[30];
		tName temp_tName;
		int temp_int;
		fgets(str, sizeof(str), fp);

		for (int i = 0; i < sizeof(str); ++i) {
			if (str[i] == ',') str[i] = '\t';
		}
		sscanf(str, "%s %c %d", temp_tName.name, &temp_tName.sex, &temp_int);

		if (names->len == 0) {
			strcpy(names->data[0].name, temp_tName.name);
			names->data[0].sex = temp_tName.sex;
			names->data[0].freq[year_index] = temp_int;
			++names->len;
		}
		else {

			int loc = binary_search(&temp_tName, names, names->len, sizeof(tName), compare);
			
			int check_exist = 0;
			if ((strcmp(names->data[loc].name, temp_tName.name) == 0) && (names->data[loc].sex == temp_tName.sex)) {
				names->data[loc].freq[year_index] = temp_int;
				check_exist = 1;
			}

			if (!check_exist) {
				if (names->len == names->capacity) {
					names->data = (tName*)realloc(names->data, 2 * names->capacity * sizeof(tName));
					names->capacity *= 2;
					for (int i = names->len; i < names->capacity; ++i) {
						memset(names->data[i].freq, 0, sizeof(names->data[i].freq));
					}
				}

				if (loc != names->len) {
					memmove(&(names->data[loc + 1]), &(names->data[loc]), (names->len - loc) * sizeof(tName));
					memset(names->data[loc].freq, 0, sizeof(names->data[loc].freq));
				}

				strcpy(names->data[loc].name, temp_tName.name);
				names->data[loc].sex = temp_tName.sex;
				names->data[loc].freq[year_index] = temp_int;
				++names->len;
			}
		}
	} while (feof(fp) == 0);
}

void print_names(tNames* names, int num_year) {
	FILE* fp = fopen("result.txt", "w");

	for (int i = 0; i < names->len; ++i) {
		fprintf(fp, "%s\t%c\t", names->data[i].name, names->data[i].sex);
		for (int j = 0; j < num_year; ++j) {
			fprintf(fp, "%d\t", names->data[i].freq[j]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);
}

int compare(const void* n1, const void* n2) {
	tName data1 = *(tName*)n1;
	tName data2 = *(tName*)n2;

	if (strcmp(data1.name, data2.name) < 0) return -1;
	else if (strcmp(data1.name, data2.name) > 0) return 1;
	else return data1.sex - data2.sex;
}

int binary_search(const void* key, const void* base, size_t nmemb, size_t size, int (*compare)(const void*, const void*)) {
	tName k = *(tName*)key;
	tNames* b;
	b = (tNames*)base;

	int l = 0;
	int r = nmemb - 1;

	while (l <= r) {
		int m = (l + r) / 2;

		if (!compare(&k, &b->data[m])) return m;
		else if (compare(&k, &b->data[m]) > 0) l = m + 1;
		else r = m - 1;
	}

	return l;
}
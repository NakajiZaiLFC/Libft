/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/17 17:42:18 by alelievr          #+#    #+#             */
/*   Updated: 2015/11/26 21:47:28 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_test.h"

#define		STRING_1	"the cake is a lie !\0I'm hidden lol\r\n"
#define		STRING_4	"phrase differente pour le test"
#define		STRING_2	"there is no starts in the sky"
#define		STRING_3	"test basic !"

#define		REG(x)		((x > 0) ? 1 : ((x < 0) ? -1 : 0))

void			add_fun_subtest(void (*fun)(void *ptr)) {
	static int		index = 0;

	if (index >= SUBTEST_SIZE)
		return ;
	fun_subtest_table[index].fun_name = current_fun_name;
	fun_subtest_table[index].fun_test_ptr = fun;
	fun_subtest_table[index].visible = current_fun_visibility;
	index++;
	total_subtest++;
}

////////////////////////////////
//         ft_memset          //
////////////////////////////////

void			test_ft_memset_basic(void *ptr) {
	typeof(memset)	*ft_memset = ptr;

	SET_EXPLICATION("basic memset test (fill a buffer with 'A')");

	//Auto raise: if crash => a TEST_CRASH is raised otherwise the return of the sandbox is raised
	SANDBOX_RAISE(
			char	b1[BSIZE + 1];
			char	b2[BSIZE + 1];

			b1[BSIZE] = 0;
			b2[BSIZE] = 0;
			memset(b1, 'A', BSIZE);
			ft_memset(b2, 'A', BSIZE);

			if (!strcmp(b1, b2))
				exit(TEST_SUCCESS);
			SET_DIFF(b1, b2);
			exit(TEST_SUCCESS);
			);
}

void			test_ft_memset_fat(void *ptr) {
	typeof(memset)	*ft_memset = ptr;

	SET_EXPLICATION("basic memset test (fill a buffer with 'A')");

	SANDBOX_RAISE(
			char	*b1 = (char*)malloc(sizeof(char) * (BFSIZE + 1));
			char	*b2 = (char*)malloc(sizeof(char) * (BFSIZE + 1));

			*b1 = 0;
			*b2 = 0;
			memset(b1, '\5', BFSIZE);
			ft_memset(b2, '\5', BFSIZE);

			if (!strcmp(b1, b2))
				exit(TEST_SUCCESS);
			SET_DIFF(b1, b2);
			exit(TEST_FAILED);
			);
}

void			test_ft_memset_null(void *ptr) {
	typeof(memset)	*ft_memset = ptr;
	SET_EXPLICATION("your memset does not segfault when null parameter is sent !");

	SANDBOX_IRAISE(
			ft_memset(NULL, 'a', 12);
		   );
}

void			test_ft_memset_zero_value(void *ptr) {
	typeof(memset)	*ft_memset = ptr;
	SET_EXPLICATION("your memset change something when call with a size of 0 !");

	SANDBOX_RAISE(
			char	buff[BSIZE] = {[BSIZE - 1]=0};
			char	buff2[BSIZE] = {[BSIZE - 1]=0};

			ft_memset(buff, '\xff', 0);
			memset(buff2, '\xff', 0);
			if (!memcmp(buff, buff2, BSIZE))
				exit(TEST_SUCCESS);
			SET_DIFF(buff, buff2);
			exit(TEST_FAILED);
		   );
}

void            test_ft_memset(void) {
	add_fun_subtest(test_ft_memset_basic);
	add_fun_subtest(test_ft_memset_null);
	add_fun_subtest(test_ft_memset_zero_value);
	add_fun_subtest(test_ft_memset_fat);
}

////////////////////////////////
//         ft_bzero           //
////////////////////////////////

void			test_ft_bzero_basic(void *ptr) {
	typeof(bzero)	*ft_bzero = ptr;

	SET_EXPLICATION("bzero with normal params fail !");

	SANDBOX_RAISE(
			char	str[BSIZE];
			char	str2[BSIZE];

			memset(str, 'a', BSIZE);
			memset(str2, 'a', BSIZE);

			bzero(str, 60);
			ft_bzero(str2, 60);
			if (!memcmp(str, str2, BSIZE))
				exit(TEST_SUCCESS);
			SET_DIFF(str, str2);
			exit(TEST_FAILED);
			);
}

void			test_ft_bzero_zero_value(void *ptr) {
	typeof(bzero)	*ft_bzero = ptr;

	SET_EXPLICATION("your bzero change something when call with 0 !");

	SANDBOX_RAISE(
			char	buff[BSIZE] = {[BSIZE - 1]=0};
			char	buff2[BSIZE] = {[BSIZE - 1]=0};

			ft_bzero(buff, 0);
			bzero(buff2, 0);
			if (!memcmp(buff, buff2, BSIZE))
				exit(TEST_SUCCESS);
			SET_DIFF(buff, buff2);
			exit(TEST_FAILED);
		   );
}

void			test_ft_bzero_null(void *ptr) {
	typeof(bzero)	*ft_bzero = ptr;
	SET_EXPLICATION("your bzero does not segfault when null params is sent");

	SANDBOX_IRAISE(
			ft_bzero(NULL, 0x12);
			);
}


void            test_ft_bzero(void){
	add_fun_subtest(test_ft_bzero_basic);
	add_fun_subtest(test_ft_bzero_zero_value);
	add_fun_subtest(test_ft_bzero_null);
}

////////////////////////////////
//         ft_memcpy          //
////////////////////////////////


void			test_ft_memcpy_basic_test(void *ptr) {
	typeof(memcpy)	*ft_memcpy = ptr;
	SET_EXPLICATION("your memcpy doesn't work with basic params");

	SANDBOX_RAISE(
			char	src[] = "test basic du memcpy !";
			char	buff1[22];
			char	buff2[22];

			memcpy(buff1, src, 22);
			ft_memcpy(buff2, src, 22);
			if (!memcmp(buff1, buff2, 22))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);

}

void			test_ft_memcpy_zero_value(void *ptr) {
	typeof(memcpy)	*ft_memcpy = ptr;
	SET_EXPLICATION("your memcpy does not work when call with 0");

	SANDBOX_RAISE(
			char	buff[] = "test 0 du memcpy !";
			char	*src = STRING_4;
			char	buff2[] = STRING_4;

			ft_memcpy(buff2, buff, 0);
			if (!memcmp(src, buff2, strlen(buff2)))
				exit(TEST_SUCCESS);
			SET_DIFF(src, buff2);
			exit(TEST_FAILED);
			);

}

void			test_ft_memcpy_basic_test2(void *ptr) {
	typeof(memcpy)	*ft_memcpy = ptr;
	SET_EXPLICATION("your memcpy does not work with basic params");

	SANDBOX_RAISE(
			char	src[] = STRING_3;
			char	buff1[] = STRING_1;
			char	buff2[] = STRING_1;

			memcpy(buff1, src, strlen(src));
			ft_memcpy(buff2, src, strlen(src));
			if (!memcmp(buff1, buff2, strlen(buff2)))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);

}

void			test_ft_memcpy_to_small(void *ptr) {
	typeof(memcpy)	*ft_memcpy = ptr;
	SET_EXPLICATION("your memcpy does not segfault dst is not big enough");

	SANDBOX_IRAISE(
			ft_memcpy("", "segfaulter tu dois", 17);
			);
}

void			test_ft_memcpy_struct(void *ptr) {
	typeof(memcpy)	*ft_memcpy = ptr;
	SET_EXPLICATION("your memcpy does not work with basic params");
	t_test src = {"nyancat® inside", (void*)0xdeadbeef, 0x42424242424242L, 0b1010100010};

	SANDBOX_RAISE(
			char	buff1[0xF00];
			char	buff2[0xF00];

			memcpy(buff1, &src, sizeof(src));
			ft_memcpy(buff2, &src, sizeof(src));
			if (!memcmp(buff1, buff2, strlen(buff2)))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);

}

void			test_ft_memcpy_null1(void *ptr) {
	typeof(memcpy)	*ft_memcpy = ptr;
	SET_EXPLICATION("your memcpy does not segv with NULL on first params");

	SANDBOX_IRAISE(
			ft_memcpy(NULL, "segfaulter tu dois", 17);
			);
}

void			test_ft_memcpy_null2(void *ptr) {
	typeof(memcpy)	*ft_memcpy = ptr;
	SET_EXPLICATION("your memcpy does not segv with NULL on second params");

	SANDBOX_IRAISE(
			ft_memcpy("            ", NULL, 17);
			);
}

void            test_ft_memcpy(void){
	add_fun_subtest(test_ft_memcpy_basic_test);
	add_fun_subtest(test_ft_memcpy_zero_value);
	add_fun_subtest(test_ft_memcpy_basic_test2);
	add_fun_subtest(test_ft_memcpy_to_small);
	add_fun_subtest(test_ft_memcpy_struct);
	add_fun_subtest(test_ft_memcpy_null1);
	add_fun_subtest(test_ft_memcpy_null2);
}

////////////////////////////////
//         ft_memccpy         //
////////////////////////////////

/*void			test_ft_memcpy_basic_test(void *ptr) {
	typeof(memcpy)	*ft_memcpy = ptr;
	SET_EXPLICATION("your memcpy doesn't work with basic params");

	SANDBOX_RAISE(
			char	buff[] = "test basic du memcpy !";
			char	buff2[22];

			ft_memcpy(buff2, buff, 22);
			if (memcmp(buff, buff2, 22))
				exit(TEST_FAILED);
			exit(TEST_SUCCESS);
			);

}

void			test_ft_memcpy_zero_value(void *ptr) {
	typeof(memcpy)	*ft_memcpy = ptr;
	SET_EXPLICATION("your memcpy does not work when call with 0");

	SANDBOX_RAISE(
			char	buff[] = "test 0 du memcpy !";
			char	buff2[] = "phrase differente pour le test";

			ft_memcpy(buff2, buff, 0);
			if (memcmp("phrase differente pour le test", buff2, strlen(buff2)))
				exit(TEST_FAILED);
			exit(TEST_SUCCESS);
			);

}

void			test_ft_memcpy_basic_test2(void *ptr) {
	typeof(memcpy)	*ft_memcpy = ptr;
	SET_EXPLICATION("your memcpy does not work with basic params");

	SANDBOX_RAISE(
			char	buff[] = "test basic numero 2";
			char	buff2[] = "phrase differente pour le test";

			ft_memcpy(buff2, buff, strlen(buff));
			if (memcmp("test basic numero 2our le test", buff2, strlen(buff2)))
				exit(TEST_FAILED);
			exit(TEST_SUCCESS);
			);

}

void			test_ft_memcpy_to_small(void *ptr) {
	typeof(memcpy)	*ft_memcpy = ptr;
	SET_EXPLICATION("your memcpy does not segfault dst is not big enough");

	SANDBOX_IRAISE(
			ft_memcpy("", "segfaulter tu dois", 17);
			);
}

void			test_ft_memcpy_null1(void *ptr) {
	typeof(memcpy)	*ft_memcpy = ptr;
	SET_EXPLICATION("your memcpy does not segv with NULL on first params");

	SANDBOX_IRAISE(
			ft_memcpy(NULL, "segfaulter tu dois", 17);
			);
}

void			test_ft_memcpy_null2(void *ptr) {
	typeof(memcpy)	*ft_memcpy = ptr;
	SET_EXPLICATION("your memcpy does not segv with NULL on second params");

	SANDBOX_IRAISE(
			ft_memcpy("            ", NULL, 17);
			);
}
*/
void            test_ft_memccpy(void){
/*	add_fun_subtest(test_ft_memccpy_basic_test);
	add_fun_subtest(test_ft_memccpy_zero_value);
	add_fun_subtest(test_ft_memccpy_basic_test2);
	add_fun_subtest(test_ft_memccpy_to_small);
	add_fun_subtest(test_ft_memccpy_null1);
	add_fun_subtest(test_ft_memccpy_null2);
*/}

////////////////////////////////
//         ft_memmove         //
////////////////////////////////

void			test_ft_memmove_basic(void *ptr) {
	typeof(memmove)		*ft_memmove = ptr;
	SET_EXPLICATION("your memmove does not works with basic input");

	SANDBOX_RAISE(
			char	*src = "this is a good nyancat !\r\n";
			char	dst1[0xF0];
			char	dst2[0xF0];
			int		size = strlen(src);

			memmove(dst1, src, size);
			ft_memmove(dst2, src, size);
			if (!memcmp(dst1, dst2, size))
				exit(TEST_SUCCESS);
			SET_DIFF(dst1, dst2);
			exit(TEST_FAILED);
			);
}

void			test_ft_memmove_null_byte(void *ptr) {
	typeof(memmove)		*ft_memmove = ptr;
	SET_EXPLICATION("your memmove does not works with \\0 and others unsigned char codes");

	SANDBOX_RAISE(
			char	*src = "thi\xffs i\xfas \0a g\xde\xadood \0nyan\0cat\0 !\r\n";
			int		size = 33;
			char	dst1[0xF0];
			char	dst2[0xF0];

			memmove(dst1, src, size);
			ft_memmove(dst2, src, size);
			if (!memcmp(dst1, dst2, size))
				exit(TEST_SUCCESS);
			SET_DIFF(dst1, dst2);
			exit(TEST_FAILED);
			);
}

void			test_ft_memmove_long_int(void *ptr) {
	typeof(memmove)		*ft_memmove = ptr;
	SET_EXPLICATION("your memmove does not works with integers copy");

	SANDBOX_RAISE(
			unsigned long	src = 0xdeadbeef;
			int		size = sizeof(src);
			unsigned long	dst1;
			unsigned long	dst2;

			memmove(&dst1, &src, size);
			ft_memmove(&dst2, &src, size);
			if (!memcmp(&dst1, &dst2, size))
				exit(TEST_SUCCESS);
			exit(TEST_FAILED);
			);
}

void			test_ft_memmove_overlap(void *ptr) {
	typeof(memmove)		*ft_memmove = ptr;
	SET_EXPLICATION("your memmove does not support the overlap");

	SANDBOX_RAISE(
			char	dst1[0xF0];
			char	dst2[0xF0];
			char	*data = "thiß ß\xde\xad\xbe\xeftriñg will be øvérlapéd !\r\n";
			int		size = 0xF0 - 4;

			memcpy(dst1, data, strlen(data));
			memcpy(dst2, data, strlen(data));
			memmove(dst1 + 3, dst2, size);
			ft_memmove(dst2 + 3, dst2, size);
			if (!memcmp(dst1, dst2, size))
				exit(TEST_SUCCESS);
			SET_DIFF(dst1, dst2);
			exit(TEST_FAILED);
			);
}

void			test_ft_memmove_null1(void *ptr) {
	typeof(memmove)		*ft_memmove = ptr;
	SET_EXPLICATION("your memmove does not segfault when null params is sent");

	SANDBOX_IRAISE(
			char	b[0xF0];

			ft_memmove(NULL, b, 5);
			);
}

void			test_ft_memmove_null2(void *ptr) {
	typeof(memmove)		*ft_memmove = ptr;
	SET_EXPLICATION("your memmove does not segfault when null params is sent");

	SANDBOX_IRAISE(
			char	b[0xF0];

			ft_memmove(b, NULL, 5);
			);
}

void			test_ft_memmove_same_pointer(void *ptr) {
	typeof(memmove)		*ft_memmove = ptr;
	SET_EXPLICATION("your memmove does not support the overlap");

	SANDBOX_RAISE(
			char	data1[] = STRING_1;
			char	data2[] = STRING_1;
			int		size = strlen(STRING_1);

			memmove(data1, data1, size);
			ft_memmove(data2, data2, size);
			if (!memcmp(data1, data2, size))
				exit(TEST_SUCCESS);
			SET_DIFF(data1, data2);
			exit(TEST_FAILED);
			);
}

void			test_ft_memmove_malloc_null(void *ptr) {
	typeof(memmove)		*ft_memmove = ptr;
	SET_EXPLICATION("your malloc is not protected (you should not malloc for this)");

	SANDBOX_RAISE(
			char	*src = STRING_1;
			char	buff[0xF0];

			MALLOC_NULL;
			memmove(buff, src, 100);
			MALLOC_RESET;
			exit(TEST_SUCCESS);
			);
	(void)ft_memmove;
}

void            test_ft_memmove(void){
	add_fun_subtest(test_ft_memmove_basic);
	add_fun_subtest(test_ft_memmove_null_byte);
	add_fun_subtest(test_ft_memmove_long_int);
	add_fun_subtest(test_ft_memmove_overlap);
	add_fun_subtest(test_ft_memmove_same_pointer);
	add_fun_subtest(test_ft_memmove_null1);
	add_fun_subtest(test_ft_memmove_null2);
	add_fun_subtest(test_ft_memmove_malloc_null);
}

////////////////////////////////
//         ft_memchr          //
////////////////////////////////

void			test_ft_memchr_basic(void *ptr) {
	typeof(memchr)		*ft_memchr = ptr;
	SET_EXPLICATION("your memchr does not works with basic input");

	SANDBOX_RAISE(
			char			*src = "/|\x12\xff\x09\x42\042\42|\\";
			int				size = 10;

			if (memchr(src, '\x42', size) == ft_memchr(src, '\x42', size))
				exit(TEST_SUCCESS);
			exit(TEST_FAILED);
			);
}

void			test_ft_memchr_not_found1(void *ptr) {
	typeof(memchr)		*ft_memchr = ptr;
	SET_EXPLICATION("your memchr does not works");

	SANDBOX_RAISE(
			char			*src = "/|\x12\xff\x09\x42\042\42|\\";
			int				size = 2;

			if (memchr(src, '\x42', size) == ft_memchr(src, '\x42', size))
				exit(TEST_SUCCESS);
			exit(TEST_FAILED);
			);
}

void			test_ft_memchr_not_found2(void *ptr) {
	typeof(memchr)		*ft_memchr = ptr;
	SET_EXPLICATION("your memchr does not works");

	SANDBOX_RAISE(
			char			*src = "/|\x12\xff\x09\x42\042\42|\\";
			int				size = 10;

			if (memchr(src, '\xde', size) == ft_memchr(src, '\xde', size))
				exit(TEST_SUCCESS);
			exit(TEST_FAILED);
			);
}

void			test_ft_memchr_null_byte(void *ptr) {
	typeof(memchr)		*ft_memchr = ptr;
	SET_EXPLICATION("your memchr failed to find a \\0");

	SANDBOX_RAISE(
			char			*src = "/|\x12\xff\x09\0\x42\042\0\42|\\";
			int				size = 12;

			if (memchr(src, '\0', size) == ft_memchr(src, '\0', size))
				exit(TEST_SUCCESS);
			exit(TEST_FAILED);
			);
}

void			test_ft_memchr_null(void *ptr) {
	typeof(memchr)		*ft_memchr = ptr;
	SET_EXPLICATION("your memchr does not segfault when null param is sent");

	SANDBOX_IRAISE(
			ft_memchr(NULL, '\0', 0x20);
			);
}

void            test_ft_memchr(void) {
	add_fun_subtest(test_ft_memchr_basic);
	add_fun_subtest(test_ft_memchr_not_found1);
	add_fun_subtest(test_ft_memchr_not_found2);
	add_fun_subtest(test_ft_memchr_null_byte);
	add_fun_subtest(test_ft_memchr_null);
}

////////////////////////////////
//         ft_memcmp          //
////////////////////////////////

void			test_ft_memcmp_basic(void *ptr) {
	typeof(memcmp)		*ft_memcmp = ptr;
	SET_EXPLICATION("your memcmp does not works with basic input");

	SANDBOX_RAISE(
			uint8_t	*s1 = (uint8_t *)"\xff\xaa\xde\x12MACOSX";
			uint8_t	*s2 = (uint8_t *)"\xff\xaa\xde\x12MACOSX";
			size_t	size = 10;

			if (memcmp(s1, s2, size) == ft_memcmp(s1, s2, size))
				exit(TEST_SUCCESS);
			SET_DIFF_INT(memcmp(s1, s2, size), memcmp(s1, s2, size));
			exit(TEST_FAILED);
			);
}

void			test_ft_memcmp_basic1(void *ptr) {
	typeof(memcmp)		*ft_memcmp = ptr;
	SET_EXPLICATION("your memcmp does not works with basic input");

	SANDBOX_RAISE(
			uint8_t	*s1 = (uint8_t *)"\xff\xaa\xde\x12OLOL";
			uint8_t	*s2 = (uint8_t *)"\xff\xaa\xde\x12MACOSX";
			size_t	size = 7;

			int		i1 = memcmp(s1, s2, size);
			int		i2 = REG(ft_memcmp(s1, s2, size));
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
	(void)ft_memcmp;
}

void			test_ft_memcmp_basic2(void *ptr) {
	typeof(memcmp)		*ft_memcmp = ptr;
	SET_EXPLICATION("your memcmp does not works with basic input");

	SANDBOX_RAISE(
			uint8_t	*s1 = (uint8_t *)"\xff\xaa\xde\x12";
			uint8_t	*s2 = (uint8_t *)"\xff\xaa\xde\x12MACOSAAAAA";
			size_t	size = 4;

			if (memcmp(s1, s2, size) == ft_memcmp(s1, s2, size))
				exit(TEST_SUCCESS);
			SET_DIFF_INT(memcmp(s1, s2, size), ft_memcmp(s1, s2, size));
			exit(TEST_FAILED);
			);
}

void			test_ft_memcmp_basic3(void *ptr) {
	typeof(memcmp)		*ft_memcmp = ptr;
	SET_EXPLICATION("your memcmp does not works with basic input");

	SANDBOX_RAISE(
			uint8_t	*s1 = (uint8_t *)"\xff\xaa\xde\xffMACOSX\xff";
			uint8_t	*s2 = (uint8_t *)"\xff\xaa\xde\x02";
			size_t	size = 8;

			if (memcmp(s1, s2, size) == ft_memcmp(s1, s2, size))
				exit(TEST_SUCCESS);
			SET_DIFF_INT(memcmp(s1, s2, size), ft_memcmp(s1, s2, size));
			exit(TEST_FAILED);
			);
}

void			test_ft_memcmp_null_byte(void *ptr) {
	typeof(memcmp)		*ft_memcmp = ptr;
	SET_EXPLICATION("your memcmp does not works with basic input");

	SANDBOX_RAISE(
			uint8_t	*s1 = (uint8_t *)"\xff\0\0\xaa\0\xde\xffMACOSX\xff";
			uint8_t	*s2 = (uint8_t *)"\xff\0\0\xaa\0\xde\x00MBS";
			size_t	size = 9;

			if (memcmp(s1, s2, size) == ft_memcmp(s1, s2, size))
				exit(TEST_SUCCESS);
			SET_DIFF_INT(memcmp(s1, s2, size), ft_memcmp(s1, s2, size));
			exit(TEST_FAILED);
			);
}

void			test_ft_memcmp_null1(void *ptr) {
	typeof(memcmp)		*ft_memcmp = ptr;
	SET_EXPLICATION("your memcmp does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			char	b1[] = "nyancat";

			ft_memcmp(NULL, b1, 4);
			);
}

void			test_ft_memcmp_null2(void *ptr) {
	typeof(memcmp)		*ft_memcmp = ptr;
	SET_EXPLICATION("your memcmp does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			char	b1[] = "nyancat";

			ft_memcmp(b1, NULL, 4);
			);
}

void            test_ft_memcmp(void){
	add_fun_subtest(test_ft_memcmp_basic);
	add_fun_subtest(test_ft_memcmp_basic1);
	add_fun_subtest(test_ft_memcmp_basic2);
	add_fun_subtest(test_ft_memcmp_basic3);
	add_fun_subtest(test_ft_memcmp_null_byte);
	add_fun_subtest(test_ft_memcmp_null1);
	add_fun_subtest(test_ft_memcmp_null2);
}

////////////////////////////////
//         ft_strlen          //
////////////////////////////////

void			test_ft_strlen_zero(void *ptr) {
	typeof(strlen)	*ft_strlen = ptr;
	SET_EXPLICATION("your strlen doesn't work with a \\0 inside the string");

	SANDBOX_RAISE(

			if (ft_strlen("HAHAHAHA \0 TA FAIL XD") != 9)
				exit(TEST_FAILED);
			exit(TEST_SUCCESS);
			);

}

void			test_ft_strlen_empty(void *ptr) {
	typeof(strlen)	*ft_strlen = ptr;
	SET_EXPLICATION("your strlen doesn't work with an empty string");

	SANDBOX_RAISE(

			if (ft_strlen(""))
				exit(TEST_FAILED);
			exit(TEST_SUCCESS);
			);

}

void			test_ft_strlen_null(void *ptr) {
	typeof(strlen)	*ft_strlen = ptr;
	SET_EXPLICATION("your strlen does not segv when null is sended");

	SANDBOX_IRAISE(
			ft_strlen(NULL);
			);
}

void			test_ft_strlen_basic(void *ptr) {
	typeof(strlen)	*ft_strlen = ptr;
	SET_EXPLICATION("your strlen doesn't work with basic test");

	SANDBOX_RAISE(

			if (ft_strlen("sais-tu compter ?") != strlen("parceque lui oui!"))
				exit(TEST_FAILED);
			exit(TEST_SUCCESS);
			);

}

void            test_ft_strlen(void){

	add_fun_subtest(test_ft_strlen_basic);
	add_fun_subtest(test_ft_strlen_null);
	add_fun_subtest(test_ft_strlen_empty);
	add_fun_subtest(test_ft_strlen_zero);
}

////////////////////////////////
//         ft_strdup          //
////////////////////////////////

void			test_ft_strdup_last_char(void *ptr) {
	typeof(strdup)	*ft_strdup = ptr;
	SET_EXPLICATION("your strdup does not add \\0 at the end of the sring");

	SANDBOX_RAISE(
			char 	*str;
			char	*tmp = "HAHAHA \0 tu me vois pas !";

			MALLOC_MEMSET;
			str = ft_strdup(tmp);
			MALLOC_RESET;
			if (strcmp(str, tmp))
				exit(TEST_FAILED);
			free(str);
			exit(TEST_SUCCESS);
			);
}

void			test_ft_strdup_zero(void *ptr) {
	typeof(strdup)	*ft_strdup = ptr;
	SET_EXPLICATION("your strdup don't work with empty string");

	SANDBOX_RAISE(
			char 	*str;
			char	*tmp = "";

			str = ft_strdup(tmp);
			if (strcmp(str, tmp))
				exit(TEST_FAILED);
			free(str);
			exit(TEST_SUCCESS);
			);
}

void			test_ft_strdup_null(void *ptr) {
	typeof(strdup)	*ft_strdup = ptr;
	SET_EXPLICATION("your strdup does not segv with NULL");

	SANDBOX_IRAISE(
			ft_strdup(NULL);
			);
}

void			test_ft_strdup_malloc_null(void *ptr) {
	typeof(strdup)	*ft_strdup = ptr;
	SET_EXPLICATION("you dindn't protect your malloc return");

	SANDBOX_RAISE(
			char	*ptr;

			MALLOC_NULL;
			ptr = ft_strdup("lol");
			MALLOC_RESET;
			if (!ptr)
				exit(TEST_SUCCESS);
			SET_DIFF_PTR(NULL, ptr);
			exit(TEST_FAILED);
			);
	(void)ft_strdup;
}

void			test_ft_strdup_basic(void *ptr) {
	typeof(strdup)	*ft_strdup = ptr;
	SET_EXPLICATION("your strdup doesn't works with basic input");

	SANDBOX_RAISE(
			char	*str;
			char	*tmp = "I malloc so I am.";
			
			str = ft_strdup(tmp);
			if (strcmp(str, tmp))
				exit(TEST_FAILED);
			free(str);
			exit(TEST_SUCCESS);
			);

}

void            test_ft_strdup(void){

	add_fun_subtest(test_ft_strdup_malloc_null);
	add_fun_subtest(test_ft_strdup_basic);
	add_fun_subtest(test_ft_strdup_zero);
	add_fun_subtest(test_ft_strdup_last_char);
	add_fun_subtest(test_ft_strdup_null);
}

////////////////////////////////
//         ft_strcpy          //
////////////////////////////////

void			test_ft_strcpy_basic(void *ptr) {
	typeof(strcpy)	*ft_strcpy = ptr;
	SET_EXPLICATION("your strcpy does not works with basic input");

	SANDBOX_RAISE(
			char	*src = "--> nyancat <--\n\r";
			char	dst1[30] = {[29]='a'};
			char	dst2[30] = {[29]='a'};

			strcpy(dst1, src);
			ft_strcpy(dst2, src);
			if (strcmp(dst1, dst2)) {
				SET_DIFF(dst1, dst2);
				exit(TEST_FAILED);
			}
			exit(TEST_SUCCESS);
			);
}

void			test_ft_strcpy_unicode(void *ptr) {
	typeof(strcpy)	*ft_strcpy = ptr;
	SET_EXPLICATION("your strcpy does not support unicode ?");

	SANDBOX_RAISE(
			char	*src = "œð˛ʼˇ,´˛ˀ-ºª•¶ªˆ§´";
			char	dst1[80] = {[79]='a'};
			char	dst2[80] = {[79]='a'};

			strcpy(dst1, src);
			ft_strcpy(dst2, src);
			if (strcmp(dst1, dst2)) {
				SET_DIFF(dst1, dst2);
				exit(TEST_FAILED);
			}
			exit(TEST_SUCCESS);
			);
}

void			test_ft_strcpy_empty(void *ptr) {
	typeof(strcpy)	*ft_strcpy = ptr;
	SET_EXPLICATION("your strcpy does not works with an empty string");

	SANDBOX_RAISE(
			char	*src = "";
			char	dst1[30] = {[29]='a'};
			char	dst2[30] = {[29]='a'};

			strcpy(dst1, src);
			ft_strcpy(dst2, src);
			if (strcmp(dst1, dst2)) {
				SET_DIFF(dst1, dst2);
				exit(TEST_FAILED);
			}
			exit(TEST_SUCCESS);
			);
}

void			test_ft_strcpy_null1(void *ptr) {
	typeof(strcpy)	*ft_strcpy = ptr;
	SET_EXPLICATION("your strcpy does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			ft_strcpy(NULL, "olol");
			);
}

void			test_ft_strcpy_null2(void *ptr) {
	typeof(strcpy)	*ft_strcpy = ptr;
	SET_EXPLICATION("your strcpy does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			char	b[0xF0] = {0};

			ft_strcpy(b, NULL);
			);
}

void            test_ft_strcpy(void) {
	add_fun_subtest(test_ft_strcpy_basic);
	add_fun_subtest(test_ft_strcpy_unicode);
	add_fun_subtest(test_ft_strcpy_empty);
	add_fun_subtest(test_ft_strcpy_null1);
	add_fun_subtest(test_ft_strcpy_null2);
}

////////////////////////////////
//         ft_strncpy         //
////////////////////////////////

void			test_ft_strncpy_basic(void *ptr) {
	typeof(strncpy)	*ft_strncpy = ptr;
	SET_EXPLICATION("your strncpy does not works with basic input");

	SANDBOX_RAISE(
			char	*src = "--> nyancat <--\n\r";
			char	dst1[30] = {[29]='a'};
			char	dst2[30] = {[29]='a'};
			size_t	max = 12;

			strncpy(dst1, src, max);
			ft_strncpy(dst2, src, max);
			if (strcmp(dst1, dst2)) {
				SET_DIFF(dst1, dst2);
				exit(TEST_FAILED);
			}
			exit(TEST_SUCCESS);
			);
}

void			test_ft_strncpy_unicode(void *ptr) {
	typeof(strncpy)	*ft_strncpy = ptr;
	SET_EXPLICATION("your strncpy does not support unicode ?");

	SANDBOX_RAISE(
			char	*src = "œð˛ʼˇ,´˛ˀ-ºª•¶ªˆ§´";
			char	dst1[80] = {[79]='a'};
			char	dst2[80] = {[79]='a'};
			size_t	max = 16;

			strncpy(dst1, src, max);
			ft_strncpy(dst2, src, max);
			if (strcmp(dst1, dst2)) {
				SET_DIFF(dst1, dst2);
				exit(TEST_FAILED);
			}
			exit(TEST_SUCCESS);
			);
}

void			test_ft_strncpy_empty(void *ptr) {
	typeof(strncpy)	*ft_strncpy = ptr;
	SET_EXPLICATION("your strncpy does not works with an empty string");

	SANDBOX_RAISE(
			char	*src = "";
			char	dst1[30] = {[29]='a'};
			char	dst2[30] = {[29]='a'};
			size_t	max = 29;

			strncpy(dst1, src, max);
			ft_strncpy(dst2, src, max);
			if (strcmp(dst1, dst2)) {
				SET_DIFF(dst1, dst2);
				exit(TEST_FAILED);
			}
			exit(TEST_SUCCESS);
			);
	(void)ft_strncpy;
}

void			test_ft_strncpy_zero(void *ptr) {
	typeof(strncpy)	*ft_strncpy = ptr;
	SET_EXPLICATION("your strncpy does not works with an 0 as lenght");

	SANDBOX_RAISE(
			char	*src = "this is a string with a \0 inside";
			char	dst1[50] = {[49]='a'};
			char	dst2[50] = {[49]='a'};
			size_t	max = 31;

			strncpy(dst1, src, max);
			ft_strncpy(dst2, src, max);
			if (strcmp(dst1, dst2)) {
				SET_DIFF(dst1, dst2);
				exit(TEST_FAILED);
			}
			exit(TEST_SUCCESS);
			);
}

void			test_ft_strncpy_fill(void *ptr) {
	typeof(strncpy)	*ft_strncpy = ptr;
	SET_EXPLICATION("your strncpy does not fill with \\0 the rest of the dest buffer");

	SANDBOX_RAISE(
			char	*src = "stars";
			char	dst1[50] = {[49]='a'};
			char	dst2[50] = {[49]='a'};
			size_t	max = 50;

			strncpy(dst1, src, max);
			ft_strncpy(dst2, src, max);
			if (memcmp(dst1, dst2, max)) {
				SET_DIFF(dst1, dst2);
				exit(TEST_FAILED);
			}
			exit(TEST_SUCCESS);
			);
}

void			test_ft_strncpy_null1(void *ptr) {
	typeof(strncpy)	*ft_strncpy = ptr;
	SET_EXPLICATION("your strncpy does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			ft_strncpy(NULL, "olol", 3);
			);
}

void			test_ft_strncpy_null2(void *ptr) {
	typeof(strncpy)	*ft_strncpy = ptr;
	SET_EXPLICATION("your strncpy does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			char	b[0xF0] = {0};

			ft_strncpy(b, NULL, 2);
			);
}

void            test_ft_strncpy(void){
	add_fun_subtest(test_ft_strncpy_basic);
	add_fun_subtest(test_ft_strncpy_unicode);
	add_fun_subtest(test_ft_strncpy_empty);
	add_fun_subtest(test_ft_strncpy_zero);
	add_fun_subtest(test_ft_strncpy_fill);
	add_fun_subtest(test_ft_strncpy_null1);
	add_fun_subtest(test_ft_strncpy_null2);
}

////////////////////////////////
//         ft_trcat           //
////////////////////////////////

void			test_ft_strcat_basic(void *ptr) {
	typeof(strcat)	*ft_strcat = ptr;
	SET_EXPLICATION("your strcat does not works with basic input");

	SANDBOX_RAISE(
			char	*str = STRING_1;
			char	buff1[0xF00] = STRING_2;
			char	buff2[0xF00] = STRING_2;

			strcat(buff1, str);
			ft_strcat(buff2, str);
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strcat_empty1(void *ptr) {
	typeof(strcat)	*ft_strcat = ptr;
	SET_EXPLICATION("your strcat does not works with empty string as first parameter");

	SANDBOX_RAISE(
			char	*str = "";
			char	buff1[0xF00] = STRING_2;
			char	buff2[0xF00] = STRING_2;

			strcat(buff1, str);
			ft_strcat(buff2, str);
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strcat_empty2(void *ptr) {
	typeof(strcat)	*ft_strcat = ptr;
	SET_EXPLICATION("your strcat does not works with empty string as second parameter");

	SANDBOX_RAISE(
			char	*str = STRING_1;
			char	buff1[0xF00] = "";
			char	buff2[0xF00] = "";

			strcat(buff1, str);
			ft_strcat(buff2, str);
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strcat_null_byte(void *ptr) {
	typeof(strcat)	*ft_strcat = ptr;
	SET_EXPLICATION("your strcat does not set a \\0 to the end");

	SANDBOX_RAISE(
			char	*str = "n\0AAAAAAAAAAAAAAAAA";
			char	buff1[0xF00] = "\0AAAAAAAAAAAAAAAA";
			char	buff2[0xF00] = "\0AAAAAAAAAAAAAAAA";

			strcat(buff1, str);
			ft_strcat(buff2, str);
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strcat_null1(void *ptr) {
	typeof(strcat)	*ft_strcat = ptr;
	SET_EXPLICATION("your strcat does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			char	b[0xF] = "nyan !";

			ft_strcat(NULL, b);
			);
}

void			test_ft_strcat_null2(void *ptr) {
	typeof(strcat)	*ft_strcat = ptr;
	SET_EXPLICATION("your strcat does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			char	b[0xF] = "nyan !";

			ft_strcat(b, NULL);
			);
}

void            test_ft_strcat(void){
	add_fun_subtest(test_ft_strcat_basic);
	add_fun_subtest(test_ft_strcat_empty1);
	add_fun_subtest(test_ft_strcat_empty2);
	add_fun_subtest(test_ft_strcat_null_byte);
	add_fun_subtest(test_ft_strcat_null1);
	add_fun_subtest(test_ft_strcat_null2);
}

////////////////////////////////
//         ft_strncat         //
////////////////////////////////

void			test_ft_strncat_basic(void *ptr) {
	typeof(strncat)	*ft_strncat = ptr;
	SET_EXPLICATION("your strncat does not works with basic input");

	SANDBOX_RAISE(
			char	*str = STRING_1;
			char	buff1[0xF00] = STRING_2;
			char	buff2[0xF00] = STRING_2;
			size_t	max = 5;

			strncat(buff1, str, max);
			ft_strncat(buff2, str, max);
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strncat_basic1(void *ptr) {
	typeof(strncat)	*ft_strncat = ptr;
	SET_EXPLICATION("your strncat does not works with basic input");

	SANDBOX_RAISE(
			char	*str = STRING_1;
			char	buff1[0xF00] = STRING_2;
			char	buff2[0xF00] = STRING_2;
			size_t	max = 5;

			strncat(buff1, str, max);
			ft_strncat(buff2, str, max);
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strncat_basic2(void *ptr) {
	typeof(strncat)	*ft_strncat = ptr;
	SET_EXPLICATION("your strncat does not works with over length size");

	SANDBOX_RAISE(
			char	*str = STRING_1;
			char	buff1[0xF00] = STRING_2;
			char	buff2[0xF00] = STRING_2;
			size_t	max = 1000;

			strncat(buff1, str, max);
			ft_strncat(buff2, str, max);
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strncat_empty1(void *ptr) {
	typeof(strncat)	*ft_strncat = ptr;
	SET_EXPLICATION("your strcat does not works with empty string as first parameter");

	SANDBOX_RAISE(
			char	*str = "";
			char	buff1[0xF00] = STRING_2;
			char	buff2[0xF00] = STRING_2;
			size_t	max = 5;

			strncat(buff1, str, max);
			ft_strncat(buff2, str, max);
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strncat_empty2(void *ptr) {
	typeof(strncat)	*ft_strncat = ptr;
	SET_EXPLICATION("your strcat does not works with empty string as second parameter");

	SANDBOX_RAISE(
			char	*str = STRING_1;
			char	buff1[0xF00] = "";
			char	buff2[0xF00] = "";
			size_t	max = 5;

			strncat(buff1, str, max);
			ft_strncat(buff2, str, max);
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strncat_null_byte(void *ptr) {
	typeof(strncat)	*ft_strncat = ptr;
	SET_EXPLICATION("your strncat does not set a \\0 to the end");

	SANDBOX_RAISE(
			char	*str = "n\0AAAAAAAAAAAAAAAAA";
			char	buff1[0xF00] = "\0AAAAAAAAAAAAAAAA";
			char	buff2[0xF00] = "\0AAAAAAAAAAAAAAAA";
			size_t	max = 10;

			strncat(buff1, str, max);
			ft_strncat(buff2, str, max);
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strncat_null1(void *ptr) {
	typeof(strncat)	*ft_strncat = ptr;
	SET_EXPLICATION("your strncat does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			char	b[0xF] = "nyan !";

			ft_strncat(NULL, b, 2);
			);
}

void			test_ft_strncat_null2(void *ptr) {
	typeof(strncat)	*ft_strncat = ptr;
	SET_EXPLICATION("your strncat does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			char	b[0xF] = "nyan !";

			ft_strncat(b, NULL, 2);
			);
}

void            test_ft_strncat(void){
	add_fun_subtest(test_ft_strncat_basic);
	add_fun_subtest(test_ft_strncat_basic1);
	add_fun_subtest(test_ft_strncat_basic2);
	add_fun_subtest(test_ft_strncat_empty1);
	add_fun_subtest(test_ft_strncat_empty2);
	add_fun_subtest(test_ft_strncat_null_byte);
	add_fun_subtest(test_ft_strncat_null1);
	add_fun_subtest(test_ft_strncat_null2);
}

////////////////////////////////
//         ft_strlcat         //
////////////////////////////////

void			test_ft_strlcat_basic(void *ptr) {
	typeof(strlcat)	*ft_strlcat = ptr;
	SET_EXPLICATION("your strlcat does not works with basic input");

	SANDBOX_RAISE(
			char	*str = STRING_1;
			char	buff1[0xF00] = STRING_2;
			char	buff2[0xF00] = STRING_2;
			size_t	max = strlen(STRING_1) + 4;

			strlcat(buff1, str, max);
			ft_strlcat(buff2, str, max);
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strlcat_basic1(void *ptr) {
	typeof(strlcat)	*ft_strlcat = ptr;
	SET_EXPLICATION("your strlcat does not works with basic input");

	SANDBOX_RAISE(
			char	*str = STRING_1;
			char	buff1[0xF00] = STRING_2;
			char	buff2[0xF00] = STRING_2;
			size_t	max = strlen(STRING_1) + strlen(STRING_2);

			strlcat(buff1, str, max);
			ft_strlcat(buff2, str, max);
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strlcat_basic2(void *ptr) {
	typeof(strlcat)	*ft_strlcat = ptr;
	SET_EXPLICATION("your strlcat does not works with over length size");

	SANDBOX_RAISE(
			char	*str = STRING_1;
			char	buff1[0xF00] = STRING_2;
			char	buff2[0xF00] = STRING_2;
			size_t	max = 1000;

			strlcat(buff1, str, max);
			ft_strlcat(buff2, str, max);
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strlcat_empty1(void *ptr) {
	typeof(strlcat)	*ft_strlcat = ptr;
	SET_EXPLICATION("your strcat does not works with empty string as first parameter");

	SANDBOX_RAISE(
			char	*str = "";
			char	buff1[0xF00] = STRING_2;
			char	buff2[0xF00] = STRING_2;
			size_t	max = strlen(STRING_2) + 1;

			strlcat(buff1, str, max);
			ft_strlcat(buff2, str, max);
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strlcat_empty2(void *ptr) {
	typeof(strlcat)	*ft_strlcat = ptr;
	SET_EXPLICATION("your strcat does not works with empty string as second parameter");

	SANDBOX_RAISE(
			char	*str = STRING_1;
			char	buff1[0xF00] = "";
			char	buff2[0xF00] = "";
			size_t	max = strlen(STRING_1) + 1;

			strlcat(buff1, str, max);
			ft_strlcat(buff2, str, max);
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strlcat_null_byte(void *ptr) {
	typeof(strlcat)	*ft_strlcat = ptr;
	SET_EXPLICATION("your strlcat does not set a \\0 to the end");

	SANDBOX_RAISE(
			char	*str = "n\0AA";
			char	buff1[0xF00] = "\0AAAAAAAAAAAAAAAA";
			char	buff2[0xF00] = "\0AAAAAAAAAAAAAAAA";
			size_t	max = 10;

			strlcat(buff1, str, max);
			ft_strlcat(buff2, str, max);
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strlcat_null1(void *ptr) {
	typeof(strlcat)	*ft_strlcat = ptr;
	SET_EXPLICATION("your strlcat does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			char	b[0xF] = "nyan !";

			ft_strlcat(NULL, b, 2);
			);
}

void			test_ft_strlcat_null2(void *ptr) {
	typeof(strlcat)	*ft_strlcat = ptr;
	SET_EXPLICATION("your strlcat does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			char	b[0xF] = "nyan !";

			ft_strlcat(b, NULL, 2);
			);
}

void            test_ft_strlcat(void){
	add_fun_subtest(test_ft_strlcat_basic);
	add_fun_subtest(test_ft_strlcat_basic1);
	add_fun_subtest(test_ft_strlcat_basic2);
	add_fun_subtest(test_ft_strlcat_empty1);
	add_fun_subtest(test_ft_strlcat_empty2);
	add_fun_subtest(test_ft_strlcat_null_byte);
	add_fun_subtest(test_ft_strlcat_null1);
	add_fun_subtest(test_ft_strlcat_null2);
}

////////////////////////////////
//         ft_strchr          //
////////////////////////////////

void			test_ft_strchr_basic(void *ptr) {
	typeof(strchr)	*ft_strchr = ptr;
	SET_EXPLICATION("your strchr does not works with basic input");

	SANDBOX_RAISE(
			char	*src = STRING_1;

			char	*d1 = strchr(src, ' ');
			char	*d2 = ft_strchr(src, ' ');
			if (d1 == d2)
				exit(TEST_SUCCESS);
			SET_DIFF(d1, d2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strchr_not_found(void *ptr) {
	typeof(strchr)	*ft_strchr = ptr;
	SET_EXPLICATION("your strchr does not works with not found char");

	SANDBOX_RAISE(
			char	*src = STRING_1;

			char	*d1 = strchr(src, ' ');
			char	*d2 = ft_strchr(src, ' ');
			if (d1 == d2)
				exit(TEST_SUCCESS);
			SET_DIFF(d1, d2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strchr_unicode(void *ptr) {
	typeof(strchr)	*ft_strchr = ptr;
	SET_EXPLICATION("your strchr does not works with unicode");

	SANDBOX_RAISE(
			char	*src = "īœ˙ˀ˘¯ˇ¸¯.œ«‘––™ª•¡¶¢˜ˀ";

			char	*d1 = strchr(src, L'–');
			char	*d2 = ft_strchr(src, L'–');
			if (d1 == d2)
				exit(TEST_SUCCESS);
			SET_DIFF(d1, d2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strchr_zero(void *ptr) {
	typeof(strchr)	*ft_strchr = ptr;
	SET_EXPLICATION("your strchr does not works with \\0");

	SANDBOX_RAISE(
			char	*src = "there is so \0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";

			char	*d1 = strchr(src, '\0');
			char	*d2 = ft_strchr(src, '\0');
			if (d1 == d2)
				exit(TEST_SUCCESS);
			SET_DIFF(d1, d2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strchr_null(void *ptr) {
	typeof(strchr)	*ft_strchr = ptr;

	SANDBOX_IRAISE(
			ft_strchr(NULL, '\0');
			)
}

void            test_ft_strchr(void){
	add_fun_subtest(test_ft_strchr_basic);
	add_fun_subtest(test_ft_strchr_not_found);
	add_fun_subtest(test_ft_strchr_unicode);
	add_fun_subtest(test_ft_strchr_zero);
	add_fun_subtest(test_ft_strchr_null);
}

////////////////////////////////
//         ft_strrchr         //
////////////////////////////////

void			test_ft_strrchr_basic(void *ptr) {
	typeof(strrchr)	*ft_strrchr = ptr;
	SET_EXPLICATION("your strrchr does not works with basic input");

	SANDBOX_RAISE(
			char	*src = STRING_1;

			char	*d1 = strrchr(src, ' ');
			char	*d2 = ft_strrchr(src, ' ');
			if (d1 == d2)
				exit(TEST_SUCCESS);
			SET_DIFF(d1, d2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strrchr_not_found(void *ptr) {
	typeof(strrchr)	*ft_strrchr = ptr;
	SET_EXPLICATION("your strrchr does not works with not found char");

	SANDBOX_RAISE(
			char	*src = STRING_1;

			char	*d1 = strrchr(src, ' ');
			char	*d2 = ft_strrchr(src, ' ');
			if (d1 == d2)
				exit(TEST_SUCCESS);
			SET_DIFF(d1, d2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strrchr_unicode(void *ptr) {
	typeof(strrchr)	*ft_strrchr = ptr;
	SET_EXPLICATION("your strrchr does not works with unicode");

	SANDBOX_RAISE(
			char	*src = "īœ˙ˀ˘¯ˇ¸¯.œ«‘––™ª•¡¶¢˜ˀ";

			char	*d1 = strrchr(src, L'–');
			char	*d2 = ft_strrchr(src, L'–');
			if (d1 == d2)
				exit(TEST_SUCCESS);
			SET_DIFF(d1, d2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strrchr_zero(void *ptr) {
	typeof(strrchr)	*ft_strrchr = ptr;
	SET_EXPLICATION("your strrchr does not works with \\0");

	SANDBOX_RAISE(
			char	*src = "there is so \0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";

			char	*d1 = strrchr(src, '\0');
			char	*d2 = ft_strrchr(src, '\0');
			if (d1 == d2)
				exit(TEST_SUCCESS);
			SET_DIFF(d1, d2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strrchr_null(void *ptr) {
	typeof(strrchr)	*ft_strrchr = ptr;

	SANDBOX_IRAISE(
			ft_strrchr(NULL, '\0');
			)
}

void            test_ft_strrchr(void){
	add_fun_subtest(test_ft_strrchr_basic);
	add_fun_subtest(test_ft_strrchr_not_found);
	add_fun_subtest(test_ft_strrchr_unicode);
	add_fun_subtest(test_ft_strrchr_zero);
	add_fun_subtest(test_ft_strrchr_null);
}

////////////////////////////////
//         ft_strstr          //
////////////////////////////////

void			test_ft_strstr_basic(void *ptr) {
	typeof(strstr)	*ft_strstr = ptr;
	SET_EXPLICATION("your strstr does not works with basic input");

	SANDBOX_RAISE(
			char	*s1 = "FF";
			char	*s2 = "see FF your FF return FF now FF";

			char	*i1 = strstr(s1, s2);
			char	*i2 = ft_strstr(s1, s2);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strstr_not_found(void *ptr) {
	typeof(strstr)	*ft_strstr = ptr;
	SET_EXPLICATION("your strstr does not works with not found patern");

	SANDBOX_RAISE(
			char	*s1 = "can't found that";
			char	*s2 = "in this !";

			char	*i1 = strstr(s1, s2);
			char	*i2 = ft_strstr(s1, s2);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strstr_zero_len1(void *ptr) {
	typeof(strstr)	*ft_strstr = ptr;
	SET_EXPLICATION("your strstr does not works with empty strings");

	SANDBOX_RAISE(
			char	*s1 = "";
			char	*s2 = "oh no not the empty string !";

			char	*i1 = strstr(s1, s2);
			char	*i2 = ft_strstr(s1, s2);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strstr_zero_len2(void *ptr) {
	typeof(strstr)	*ft_strstr = ptr;
	SET_EXPLICATION("your strstr does not works with empty strings");

	SANDBOX_RAISE(
			char	*s1 = "oh no not the empty string !";
			char	*s2 = "";

			char	*i1 = strstr(s1, s2);
			char	*i2 = ft_strstr(s1, s2);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strstr_same_ptr(void *ptr) {
	typeof(strstr)	*ft_strstr = ptr;

	SANDBOX_RAISE(
			char	*s1 = "AAAAAAAAAAAAA";

			char	*i1 = strstr(s1, s1);
			char	*i2 = ft_strstr(s1, s1);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strstr_null1(void *ptr) {
	typeof(strstr)	*ft_strstr = ptr;
	SET_EXPLICATION("your strstr does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			ft_strstr(NULL, "fake");
			);
}

void			test_ft_strstr_null2(void *ptr) {
	typeof(strstr)	*ft_strstr = ptr;
	SET_EXPLICATION("your strstr does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			ft_strstr("fake", NULL);
			);
}

void            test_ft_strstr(void){
	add_fun_subtest(test_ft_strstr_basic);
	add_fun_subtest(test_ft_strstr_not_found);
	add_fun_subtest(test_ft_strstr_zero_len1);
	add_fun_subtest(test_ft_strstr_zero_len2);
	add_fun_subtest(test_ft_strstr_same_ptr);
	add_fun_subtest(test_ft_strstr_null2);
	add_fun_subtest(test_ft_strstr_null1);
}

////////////////////////////////
//         ft_strnstr         //
////////////////////////////////

void			test_ft_strnstr_basic(void *ptr) {
	typeof(strnstr)	*ft_strnstr = ptr;
	SET_EXPLICATION("your strnstr does not works with basic input");

	SANDBOX_RAISE(
			char	*s1 = "FF";
			char	*s2 = "see FF your FF return FF now FF";
			size_t	max = strlen(s2);

			char	*i1 = strnstr(s1, s2, max);
			char	*i2 = ft_strnstr(s1, s2, max);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strnstr_not_found(void *ptr) {
	typeof(strnstr)	*ft_strnstr = ptr;
	SET_EXPLICATION("your strnstr does not works with not found patern");

	SANDBOX_RAISE(
			char	*s1 = "FF";
			char	*s2 = "see FF your FF return FF now FF";

			char	*i1 = strnstr(s1, s2, 4);
			char	*i2 = ft_strnstr(s1, s2, 4);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strnstr_zero_len1(void *ptr) {
	typeof(strnstr)	*ft_strnstr = ptr;
	SET_EXPLICATION("your strnstr does not works with empty strings");

	SANDBOX_RAISE(
			char	*s1 = "";
			char	*s2 = "oh no not the empty string !";
			size_t	max = strlen(s2);

			char	*i1 = strnstr(s1, s2, max);
			char	*i2 = ft_strnstr(s1, s2, max);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strnstr_zero_len2(void *ptr) {
	typeof(strnstr)	*ft_strnstr = ptr;
	SET_EXPLICATION("your strnstr does not works with empty strings");

	SANDBOX_RAISE(
			char	*s1 = "oh no not the empty string !";
			char	*s2 = "";
			size_t	max = strlen(s1);

			char	*i1 = strnstr(s1, s2, max);
			char	*i2 = ft_strnstr(s1, s2, max);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strnstr_same_ptr(void *ptr) {
	typeof(strnstr)	*ft_strnstr = ptr;

	SANDBOX_RAISE(
			char	*s1 = "AAAAAAAAAAAAA";
			size_t	max = strlen(s1);

			char	*i1 = strnstr(s1, s1, max);
			char	*i2 = ft_strnstr(s1, s1, max);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strnstr_zero(void *ptr) {
	typeof(strnstr)	*ft_strnstr = ptr;

	SANDBOX_RAISE(
			char	*s1 = "A";

			char	*i1 = strnstr(s1, s1, 0);
			char	*i2 = ft_strnstr(s1, s1, 0);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strnstr_null1(void *ptr) {
	typeof(strnstr)	*ft_strnstr = ptr;
	SET_EXPLICATION("your strnstr does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			ft_strnstr(NULL, "fake", 3);
			);
}

void			test_ft_strnstr_null2(void *ptr) {
	typeof(strnstr)	*ft_strnstr = ptr;
	SET_EXPLICATION("your strnstr does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			ft_strnstr("fake", NULL, 3);
			);
}

void            test_ft_strnstr(void){
	add_fun_subtest(test_ft_strnstr_basic);
	add_fun_subtest(test_ft_strnstr_not_found);
	add_fun_subtest(test_ft_strnstr_zero_len1);
	add_fun_subtest(test_ft_strnstr_zero_len2);
	add_fun_subtest(test_ft_strnstr_same_ptr);
	add_fun_subtest(test_ft_strnstr_zero);
	add_fun_subtest(test_ft_strnstr_null2);
	add_fun_subtest(test_ft_strnstr_null1);
}

////////////////////////////////
//         ft_strcmp          //
////////////////////////////////


void			test_ft_strcmp_basic1(void *ptr) {
	typeof(strcmp)	*ft_strcmp = ptr;
	SET_EXPLICATION("your strcmp does not works with basic input");

	SANDBOX_RAISE(
			char	*s1 = STRING_1;
			char	*s2 = STRING_2;

			int		i1 = strcmp(s1, s2);
			int		i2 = REG(ft_strcmp(s1, s2));
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strcmp_basic2(void *ptr) {
	typeof(strcmp)	*ft_strcmp = ptr;
	SET_EXPLICATION("your strcmp does not works with basic input");

	SANDBOX_RAISE(
			char	*s1 = "omg1";
			char	*s2 = "omg3";

			int		i1 = strcmp(s1, s2);
			int		i2 = REG(ft_strcmp(s1, s2));
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strcmp_basic3(void *ptr) {
	typeof(strcmp)	*ft_strcmp = ptr;
	SET_EXPLICATION("your strcmp does not works with basic input");

	SANDBOX_RAISE(
			char	*s1 = "";
			char	*s2 = "";

			int		i1 = strcmp(s1, s2);
			int		i2 = REG(ft_strcmp(s1, s2));
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strcmp_ascii(void *ptr) {
	typeof(strcmp)	*ft_strcmp = ptr;
	SET_EXPLICATION("your strcmp does not works with non ascii chars");

	SANDBOX_RAISE(
			char	*s1 = "\x12\xff\x65\x12\xbd\xde\xad";
			char	*s2 = "\x12\x02";

			int		i1 = strcmp(s1, s2);
			int		i2 = REG(ft_strcmp(s1, s2));
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strcmp_null1(void *ptr) {
	typeof(strcmp)	*ft_strcmp = ptr;
	SET_EXPLICATION("your strcmp does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			ft_strcmp(NULL, "nope");
			);
}

void			test_ft_strcmp_null2(void *ptr) {
	typeof(strcmp)	*ft_strcmp = ptr;
	SET_EXPLICATION("your strcmp does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			ft_strcmp("nope", NULL);
			ft_strcmp(NULL, NULL);
			);
}

void            test_ft_strcmp(void){
	add_fun_subtest(test_ft_strcmp_basic1);
	add_fun_subtest(test_ft_strcmp_basic2);
	add_fun_subtest(test_ft_strcmp_basic3);
	add_fun_subtest(test_ft_strcmp_ascii);
	add_fun_subtest(test_ft_strcmp_null1);
	add_fun_subtest(test_ft_strcmp_null2);
}

////////////////////////////////
//         ft_strncmp         //
////////////////////////////////

void			test_ft_strncmp_basic1(void *ptr) {
	typeof(strncmp)	*ft_strncmp = ptr;
	SET_EXPLICATION("your strncmp does not works with basic input");

	SANDBOX_RAISE(
			char	*s1 = STRING_1;
			char	*s2 = STRING_2;
			size_t	size = strlen(STRING_1);

			int		i1 = strncmp(s1, s2, size);
			int		i2 = REG(ft_strncmp(s1, s2, size));
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strncmp_basic2(void *ptr) {
	typeof(strncmp)	*ft_strncmp = ptr;
	SET_EXPLICATION("your strncmp does not works with basic input");

	SANDBOX_RAISE(
			char	*s1 = "omg1||||||||||||||||";
			char	*s2 = "omg3";
			size_t	size = 4;

			int		i1 = strncmp(s1, s2, size);
			int		i2 = REG(ft_strncmp(s1, s2, size));
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strncmp_basic3(void *ptr) {
	typeof(strncmp)	*ft_strncmp = ptr;
	SET_EXPLICATION("your strncmp does not works with basic input");

	SANDBOX_RAISE(
			char	*s1 = "";
			char	*s2 = "";

			int		i1 = strncmp(s1, s2, 1);
			int		i2 = REG(ft_strncmp(s1, s2, 1));
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strncmp_over_len(void *ptr) {
	typeof(strncmp)	*ft_strncmp = ptr;
	SET_EXPLICATION("your strncmp does not works with basic input");

	SANDBOX_RAISE(
			char	*s1 = "omg1";
			char	*s2 = "omg3                ";
			size_t	size = 100000;

			int		i1 = strncmp(s1, s2, size);
			int		i2 = ft_strncmp(s1, s2, size);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
}
void			test_ft_strncmp_ascii(void *ptr) {
	typeof(strncmp)	*ft_strncmp = ptr;
	SET_EXPLICATION("your strncmp does not works with non ascii chars");

	SANDBOX_RAISE(
			char	*s1 = "\x12\xff\x65\x12\xbd\xde\xad";
			char	*s2 = "\x12\x02";
			size_t	size = 6;

			int		i1 = strncmp(s1, s2, size);
			int		i2 = ft_strncmp(s1, s2, size);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strncmp_null1(void *ptr) {
	typeof(strncmp)	*ft_strncmp = ptr;
	SET_EXPLICATION("your strncmp does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			ft_strncmp(NULL, "nope", 3);
			);
}

void			test_ft_strncmp_null2(void *ptr) {
	typeof(strncmp)	*ft_strncmp = ptr;
	SET_EXPLICATION("your strncmp does not segfault when null parameter is sent");

	SANDBOX_IRAISE(
			ft_strncmp("nope", NULL, 3);
			ft_strncmp(NULL, NULL, 3);
			);
}

void            test_ft_strncmp(void){
	add_fun_subtest(test_ft_strncmp_basic1);
	add_fun_subtest(test_ft_strncmp_basic2);
	add_fun_subtest(test_ft_strncmp_basic3);
	add_fun_subtest(test_ft_strncmp_over_len);
	add_fun_subtest(test_ft_strncmp_ascii);
	add_fun_subtest(test_ft_strncmp_null1);
	add_fun_subtest(test_ft_strncmp_null2);
}

////////////////////////////////
//         ft_atoi            //
////////////////////////////////

void			test_ft_atoi_basic(void *ptr) {
	typeof(atoi)	*ft_atoi = ptr;
	SET_EXPLICATION("your atoi does not works with positive numbers");

	SANDBOX_RAISE(
			char	*n = "945";

			int		i1 = atoi(n);
			int		i2 = ft_atoi(n);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_atoi_negative(void *ptr) {
	typeof(atoi)	*ft_atoi = ptr;
	SET_EXPLICATION("your atoi does not works with negative numbers");

	SANDBOX_RAISE(
			char	*n = "-085";

			int		i1 = atoi(n);
			int		i2 = ft_atoi(n);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_atoi_rand(void *ptr) {
	typeof(atoi)	*ft_atoi = ptr;
	SET_EXPLICATION("your atoi does not works with random numbers");

	SANDBOX_RAISE(
			srand(clock());
			for (int i = 0; i < 100; i++) {
				char n[15];
				sprintf(n, "%i", rand());

				int		i1 = atoi(n);
				int		i2 = ft_atoi(n);
				if (i1 != i2) {
					SET_DIFF_INT(i1, i2);
					exit(TEST_FAILED);
				}
			}
			exit(TEST_SUCCESS);
			);
}

void			test_ft_atoi_blank1(void *ptr) {
	typeof(atoi)	*ft_atoi = ptr;
	SET_EXPLICATION("your atoi is not working with blanks");

	SANDBOX_RAISE(
			char	*n = "\t\v\f\r\n \f-06050";

			int		i1 = atoi(n);
			int		i2 = ft_atoi(n);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_atoi_blank2(void *ptr) {
	typeof(atoi)	*ft_atoi = ptr;
	SET_EXPLICATION("your atoi is not working with blanks");

	SANDBOX_RAISE(
			char	*n = "\t\v\f\r\n \f- \f\t\n\r    06050";

			int		i1 = atoi(n);
			int		i2 = ft_atoi(n);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_atoi_string(void *ptr) {
	typeof(atoi)	*ft_atoi = ptr;
	SET_EXPLICATION("your atoi is not working with blanks");

	SANDBOX_RAISE(
			char	*n = "-123THERE IS A NYANCAT UNDER YOUR BED";

			int		i1 = atoi(n);
			int		i2 = ft_atoi(n);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_atoi_max_int(void *ptr) {
	typeof(atoi)	*ft_atoi = ptr;
	SET_EXPLICATION("your atoi does not works with int max value");

	SANDBOX_RAISE(
			char	n[15];
			sprintf(n, "%i", INT_MAX);

			int		i1 = atoi(n);
			int		i2 = ft_atoi(n);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_atoi_min_int(void *ptr) {
	typeof(atoi)	*ft_atoi = ptr;
	SET_EXPLICATION("your atoi does not works with int min value");

	SANDBOX_RAISE(
			char	n[15];
			sprintf(n, "%i", INT_MIN);

			int		i1 = atoi(n);
			int		i2 = ft_atoi(n);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_FAILED);
			);
}

void			test_ft_atoi_max_long(void *ptr) {
	typeof(atoi)	*ft_atoi = ptr;
	SET_EXPLICATION("your atoi does not works with long max value");

	SANDBOX_RAISE(
			char	n[40];
			sprintf(n, "%li", LONG_MAX);

			int		i1 = atoi(n);
			int		i2 = ft_atoi(n);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_KO);
			);
}

void			test_ft_atoi_min_long(void *ptr) {
	typeof(atoi)	*ft_atoi = ptr;
	SET_EXPLICATION("your atoi does not works with long min value");

	SANDBOX_RAISE(
			char	n[40];
			sprintf(n, "%li", LONG_MIN);

			int		i1 = atoi(n);
			int		i2 = ft_atoi(n);
			if (i1 == i2)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(i1, i2);
			exit(TEST_KO);
			);
}

void			test_ft_atoi_null(void *ptr) {
	typeof(atoi)	*ft_atoi = ptr;

	SANDBOX_IRAISE(
			ft_atoi(NULL);
			);
}

void            test_ft_atoi(void){
	add_fun_subtest(test_ft_atoi_basic);
	add_fun_subtest(test_ft_atoi_negative);
	add_fun_subtest(test_ft_atoi_rand);
	add_fun_subtest(test_ft_atoi_blank1);
	add_fun_subtest(test_ft_atoi_blank2);
	add_fun_subtest(test_ft_atoi_string);
	add_fun_subtest(test_ft_atoi_max_int);
	add_fun_subtest(test_ft_atoi_min_int);
	add_fun_subtest(test_ft_atoi_max_long);
	add_fun_subtest(test_ft_atoi_min_long);
	add_fun_subtest(test_ft_atoi_null);
}

////////////////////////////////
//         ft_isalpha         //
////////////////////////////////

#include <ctype.h>

void			test_ft_isalpha_(void *ptr) {
	typeof(isalpha)	*ft_isalpha = ptr;
	SET_EXPLICATION("your ft_isalpha just doesn't work, REALLY ?!");

	SANDBOX_RAISE(
			int		i;
			i = -1;
			while (i < 530)
			{
				if (ft_isalpha(i) != isalpha(i))
					exit(TEST_FAILED);
				i++;
			}
			exit(TEST_SUCCESS);
		);
}


void            test_ft_isalpha(void){
	add_fun_subtest(test_ft_isalpha_);
}

////////////////////////////////
//         ft_isdigit         //
////////////////////////////////

void			test_ft_isdigit_(void *ptr) {
	typeof(isdigit)	*ft_isdigit = ptr;
	SET_EXPLICATION("your ft_isdigit just doesn't work, REALLY ?!");

	SANDBOX_RAISE(
			int		i;
			i = -1;
			while (i < 530)
			{
				if (ft_isdigit(i) != isdigit(i))
					exit(TEST_FAILED);
				i++;
			}
			exit(TEST_SUCCESS);
		);
}

void            test_ft_isdigit(void){
	add_fun_subtest(test_ft_isdigit_);
}

////////////////////////////////
//         ft_isalnum         //
////////////////////////////////

void			test_ft_isalnum_(void *ptr) {
	typeof(isalnum)	*ft_isalnum = ptr;
	SET_EXPLICATION("your ft_isalnum just doesn't work, REALLY ?!");

	SANDBOX_RAISE(
			int		i;
			i = -1;
			while (i < 530)
			{
				if (ft_isalnum(i) != isalnum(i))
					exit(TEST_FAILED);
				i++;
			}
			exit(TEST_SUCCESS);
		);
}

void            test_ft_isalnum(void){
	add_fun_subtest(test_ft_isalnum_);
}

////////////////////////////////
//         ft_isascii         //
////////////////////////////////

void			test_ft_isascii_(void *ptr) {
	typeof(isascii)	*ft_isascii = ptr;
	SET_EXPLICATION("your ft_isascii just doesn't work, REALLY ?!");

	SANDBOX_RAISE(
			int		i;
			i = -1;
			while (i < 530)
			{
				if (ft_isascii(i) != isascii(i))
					exit(TEST_FAILED);
				i++;
			}
			exit(TEST_SUCCESS);
		);
}

void            test_ft_isascii(void){
	add_fun_subtest(test_ft_isascii_);
}

////////////////////////////////
//         ft_isprint         //
////////////////////////////////

void			test_ft_isprint_(void *ptr) {
	typeof(isprint)	*ft_isprint = ptr;
	SET_EXPLICATION("your ft_isprint just doesn't work, REALLY ?!");

	SANDBOX_RAISE(
			int		i;
			i = -1;
			while (i < 530)
			{
				if (ft_isprint(i) != isprint(i))
					exit(TEST_FAILED);
				i++;
			}
			exit(TEST_SUCCESS);
		);
}


void            test_ft_isprint(void){
	add_fun_subtest(test_ft_isprint_);
}

////////////////////////////////
//        ft_touupper         //
////////////////////////////////

void			test_ft_toupper_(void *ptr) {
	typeof(toupper)	*ft_toupper = ptr;
	SET_EXPLICATION("your ft_isprint just doesn't work, REALLY ?!");

	SANDBOX_RAISE(
			int		i;
			i = -100;
			while (i < 530)
			{
				if (ft_toupper(i) != toupper(i))
					exit(TEST_FAILED);
				i++;
			}
			exit(TEST_SUCCESS);
		);
}

void            test_ft_toupper(void) {
	add_fun_subtest(test_ft_toupper_);
}

////////////////////////////////
//         ft_tolower         //
////////////////////////////////

void			test_ft_tolower_(void *ptr) {
	typeof(tolower)	*ft_tolower = ptr;
	SET_EXPLICATION("your ft_isprint just doesn't work, REALLY ?!");

	SANDBOX_RAISE(
			int		i;
			i = -100;
			while (i < 530)
			{
				if (ft_tolower(i) != tolower(i))
					exit(TEST_FAILED);
				i++;
			}
			exit(TEST_SUCCESS);
		);
}

void            test_ft_tolower(void){
	add_fun_subtest(test_ft_tolower_);
}

////////////////////////////////
//        ft_memalloc         //
////////////////////////////////

//FIXME this function needs a test for \0 at end of the string

void			test_ft_memalloc_free(void *ptr) {
	void *	(*ft_memalloc)(size_t) = ptr;
	SET_EXPLICATION("your memalloc don't allocate memory");

	SANDBOX_RAISE(
			free(ft_memalloc(42));
			);
}

void			test_ft_memalloc_zero(void *ptr) {
	void *	(*ft_memalloc)(size_t) = ptr;
	SET_EXPLICATION("your memalloc does not set allocated mem to 0");

	SANDBOX_RAISE(
			size_t	size = 514;
			char	*ret = ft_memalloc(size);

			for (size_t i = 0;i < size;i++)
				if (ret[i] != 0) {
					SET_DIFF_INT(0, ret[i]);
					exit(TEST_FAILED);
				}
			free(ret);
			exit(TEST_SUCCESS);
			);
}

void			test_ft_memalloc_malloc_null(void *ptr) {
	void *	(*ft_memalloc)(size_t) = ptr;
	SET_EXPLICATION("you did not protect your malloc return");

	SANDBOX_RAISE(
			void	*ret;

			MALLOC_NULL;
			ret = ft_memalloc(42);
			MALLOC_RESET;
			if (!ret)
				exit(TEST_SUCCESS);
			SET_DIFF_PTR(NULL, ret);
			exit(TEST_FAILED);
			);
}

void			test_ft_memalloc_size(void *ptr) {
	void *	(*ft_memalloc)(size_t) = ptr;

	(void)ft_memalloc;
}

void            test_ft_memalloc(void) {
	add_fun_subtest(test_ft_memalloc_free);
	add_fun_subtest(test_ft_memalloc_zero);
	add_fun_subtest(test_ft_memalloc_malloc_null);
//	add_fun_subtest(test_ft_memalloc_size);
}

////////////////////////////////
//         ft_memdel          //
////////////////////////////////

void			test_ft_memdel_test(void *ptr) {
	void	(*ft_memdel)(void **) = ptr;

	SANDBOX_RAISE(
			void	*m = malloc(42);

			ft_memdel(&m);
			if (m == NULL)
				exit(TEST_SUCCESS);
			SET_DIFF_PTR(NULL, m);
			exit(TEST_FAILED);
			);
}

void			test_ft_memdel_free(void *ptr) {
	void	(*ft_memdel)(void **) = ptr;
	SET_EXPLICATION("your memdel does not free memory !");

	SANDBOX_RAISE(
			STDOUT_TO_BUFF;
			void	*m = malloc(42);
			ft_memdel(&m);
			if (m != NULL)
				free(m);
			write(1, "", 1);
			VOID_STDOUT;
			);
}

void			test_ft_memdel_null(void *ptr) {
	void	(*ft_memdel)(void **) = ptr;
	SET_EXPLICATION("your memdel does not segfault when null parameter is sent");

	SANDBOX(
			ft_memdel(NULL);
			);
	if (SANDBOX_CRASH)
		ft_raise(TEST_SUCCESS);
	else
		ft_raise(TEST_KO);
}

void            test_ft_memdel(void) {
	add_fun_subtest(test_ft_memdel_test);
	add_fun_subtest(test_ft_memdel_free);
	add_fun_subtest(test_ft_memdel_null);
}

////////////////////////////////
//         ft_strnew          //
////////////////////////////////

//FIXME this function needs a test for \0 at end of the string

void			test_ft_strnew_free(void *ptr) {
	void *	(*ft_strnew)(size_t) = ptr;
	SET_EXPLICATION("your strnew don't allocate memory");

	SANDBOX_RAISE(
			free(ft_strnew(42));
			);
}

//FIXME this function need to be malloc-size tested !
void			test_ft_strnew_zero(void *ptr) {
	void *	(*ft_strnew)(size_t) = ptr;
	SET_EXPLICATION("your strnew does not set allocated mem to 0");

	SANDBOX_RAISE(
			size_t	size = 514;
			char	*ret = ft_strnew(size);

			for (size_t i = 0;i < size + 1;i++)
				if (ret[i] != 0) {
					SET_DIFF_INT(0, ret[i]);
					exit(TEST_FAILED);
				}
			free(ret);
			exit(TEST_SUCCESS);
			);
}

void			test_ft_strnew_malloc_null(void *ptr) {
	void *	(*ft_strnew)(size_t) = ptr;
	SET_EXPLICATION("you did not protect your malloc return");

	SANDBOX_RAISE(
			void	*ret;

			MALLOC_NULL;
			ret = ft_strnew(42);
			MALLOC_RESET;
			if (!ret)
				exit(TEST_SUCCESS);
			SET_DIFF_PTR(NULL, ret);
			exit(TEST_FAILED);
			);
}

void            test_ft_strnew(void){
	add_fun_subtest(test_ft_strnew_free);
	add_fun_subtest(test_ft_strnew_zero);
	add_fun_subtest(test_ft_strnew_malloc_null);
}

////////////////////////////////
//         ft_strdel          //
////////////////////////////////

void			test_ft_strdel_test(void *ptr) {
	void	(*ft_strdel)(void **) = ptr;

	SANDBOX_RAISE(
			void	*m = malloc(42);

			ft_strdel(&m);
			if (m == NULL)
				exit(TEST_SUCCESS);
			SET_DIFF_PTR(NULL, m);
			exit(TEST_FAILED);
			);
}

void			test_ft_strdel_free(void *ptr) {
	void	(*ft_strdel)(void **) = ptr;
	SET_EXPLICATION("your strdel does not free memory !");

	SANDBOX_RAISE(
			STDOUT_TO_BUFF;
			void	*m = malloc(42);
			ft_strdel(&m);
			if (m != NULL)
				free(m);
			write(1, "", 1);
			VOID_STDOUT;
			);
}

void			test_ft_strdel_null(void *ptr) {
	void	(*ft_strdel)(void **) = ptr;
	SET_EXPLICATION("your strdel does not segfault when null parameter is sent");

	SANDBOX_KO(
			ft_strdel(NULL);
			);
}

void            test_ft_strdel(void){
	add_fun_subtest(test_ft_strdel_test);
	add_fun_subtest(test_ft_strdel_free);
	add_fun_subtest(test_ft_strdel_null);
}

////////////////////////////////
//         ft_strclr          //
////////////////////////////////

void			test_ft_strclr_basic(void *ptr) {
	void	(*ft_strclr)(char *) = ptr;
	SET_EXPLICATION("your strclr does not set to 0 the string");

	SANDBOX_RAISE(
			char	b[] = "strclr test !\r\n";
			char	n[0xF0];
			size_t	size = strlen(b);

			memset(n, 0, size);
			ft_strclr(b);
			if (!memcmp(b, n, size))
				exit(TEST_SUCCESS);
			SET_DIFF_INT(0, memcmp(b, n, size));
			exit(TEST_FAILED);
			);

}

void			test_ft_strclr_null(void *ptr) {
	void	(*ft_strclr)(char *) = ptr;
	SET_EXPLICATION("your strclr does not segfault when null parameter is sent");

	SANDBOX_KO(
			ft_strclr(NULL);
			);
}

void            test_ft_strclr(void){
	add_fun_subtest(test_ft_strclr_basic);
	add_fun_subtest(test_ft_strclr_null);
}

////////////////////////////////
//         ft_striter         //
////////////////////////////////

void			f_striter(char *s) { *s = 'F'; }

void			test_ft_striter_basic(void *ptr) {
	void	(*ft_striter)(char *, void (*)(char *)) = ptr;
	SET_EXPLICATION("your st does no works");

	SANDBOX_RAISE(
			char	b[] = "override this !";
			char	b2[0xF0];
			size_t	size = strlen(b);

			for (size_t i = 0; i < size; i++)
				f_striter(b2 + i);
			b2[size] = 0;
			ft_striter(b, f_striter);
			if (!strcmp(b, b2))
				exit(TEST_SUCCESS);
			SET_DIFF(b, b2);
			exit(TEST_FAILED);
			);
}

void			test_ft_striter_null1(void *ptr) {
	void	(*ft_striter)(char *, void (*)(char *)) = ptr;
	SET_EXPLICATION("your striter does not segfault when null parameter is sent");

	SANDBOX_KO(
			ft_striter(NULL, f_striter)
			);
}

void			test_ft_striter_null2(void *ptr) {
	void	(*ft_striter)(char *, void (*)(char *)) = ptr;
	SET_EXPLICATION("your striter does not segfault when null parameter is sent");

	SANDBOX_KO(
			ft_striter("you should not ...", NULL);
			);
}

void            test_ft_striter(void){
	add_fun_subtest(test_ft_striter_basic);
	add_fun_subtest(test_ft_striter_null1);
	add_fun_subtest(test_ft_striter_null2);
}

////////////////////////////////
//        ft_striteri         //
////////////////////////////////

void			f_striteri(unsigned i, char *s) { *s = i + '0'; }

void			test_ft_striteri_basic(void *ptr) {
	void	(*ft_striteri)(char *, void (*)(unsigned, char *)) = ptr;
	SET_EXPLICATION("your striteri does no works");

	SANDBOX_RAISE(
			char	b[] = "override this !";
			char	b2[0xF0];
			size_t	size = strlen(b);

			for (size_t i = 0; i < size; i++)
				f_striteri(i, b2 + i);
			b2[size] = 0;
			ft_striteri(b, f_striteri);
			if (!strcmp(b, b2))
				exit(TEST_SUCCESS);
			SET_DIFF(b, b2);
			exit(TEST_FAILED);
			);
}

void			test_ft_striteri_null1(void *ptr) {
	void	(*ft_striteri)(char *, void (*)(unsigned, char *)) = ptr;
	SET_EXPLICATION("your striteri does not segfault when null parameter is sent");

	SANDBOX_KO(
			ft_striteri(NULL, f_striteri)
			);
}

void			test_ft_striteri_null2(void *ptr) {
	void	(*ft_striteri)(char *, void (*)(unsigned, char *)) = ptr;
	SET_EXPLICATION("your striteri does not segfault when null parameter is sent");

	SANDBOX_KO(
			ft_striteri("you should not ...", NULL);
			ft_striteri(NULL, NULL);
			);
}

void            test_ft_striteri(void){
	add_fun_subtest(test_ft_striteri_basic);
	add_fun_subtest(test_ft_striteri_null1);
	add_fun_subtest(test_ft_striteri_null2);
}

////////////////////////////////
//         ft_strmap          //
////////////////////////////////

//FIXME this function needs a test for \0 at end of the string

char			f_strmap(char c) { return (c + 7); }

void			test_ft_strmap_basic(void *ptr) {
	char *	(*ft_strmap)(const char *, char (*)(char)) = ptr;
	SET_EXPLICATION("your strmap does not works");

	SANDBOX_RAISE(
			char	*b = "override this !";
			char	b2[0xF0];
			size_t	size = strlen(b);

			for (size_t i = 0; i < size; i++)
				b2[i] = f_strmap(b[i]);
			b2[size] = 0;
			char	*ret = ft_strmap(b, f_strmap);
			if (!strcmp(b2, ret))
				exit(TEST_SUCCESS);
			SET_DIFF(ret, b2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strmap_free(void *ptr) {
	char *	(*ft_strmap)(const char *, char (*)(char)) = ptr;
	SET_EXPLICATION("your strmap does not malloc ?");

	SANDBOX_RAISE(
			char	*b = "override this !";
			char	b2[0xF0];
			size_t	size = strlen(b);

			for (size_t i = 0; i < size; i++)
				b2[i] = f_strmap(b[i]);
			b2[size] = 0;
			STDOUT_TO_BUFF;
			char *newstr = ft_strmap(b, f_strmap);
			if (!strcmp(newstr, b2))
				exit(TEST_SUCCESS);
			free(newstr);
			write(1, "", 1);
			VOID_STDOUT;
			SET_DIFF(b2, newstr);
			exit(TEST_FAILED);
			);
}

void			test_ft_strmap_malloc_null(void *ptr) {
	char *	(*ft_strmap)(const char *, char (*)(char)) = ptr;
	SET_EXPLICATION("you did not protect your malloc return");

	SANDBOX_RAISE(
			char	*b = "override this !";

			MALLOC_NULL;
			char *newstr = ft_strmap(b, f_strmap);
			MALLOC_RESET;
			if (newstr == NULL)
				exit(TEST_SUCCESS);
			SET_DIFF(NULL, newstr);
			exit(TEST_FAILED);
			);
}

void			test_ft_strmap_null1(void *ptr) {
	char *	(*ft_strmap)(const char *, char (*)(char)) = ptr;
	SET_EXPLICATION("your strmap does not segfault when null parameter is sent");

	SANDBOX_KO(
			ft_strmap(NULL, f_strmap);
			);
}

void			test_ft_strmap_null2(void *ptr) {
	char *	(*ft_strmap)(const char *, char (*)(char)) = ptr;
	SET_EXPLICATION("your strmap does not segfault when null parameter is sent");

	SANDBOX_KO(
			ft_strmap("olol", NULL);
			ft_strmap(NULL, NULL);
			);
}

void            test_ft_strmap(void){
	add_fun_subtest(test_ft_strmap_basic);
	add_fun_subtest(test_ft_strmap_free);
	add_fun_subtest(test_ft_strmap_malloc_null);
	add_fun_subtest(test_ft_strmap_null1);
	add_fun_subtest(test_ft_strmap_null2);
}

////////////////////////////////
//         ft_strmapi         //
////////////////////////////////

//FIXME this function needs a test for \0 at end of the string

char			f_strmapi(unsigned i, char c) { return (c + i); }

void			test_ft_strmapi_basic(void *ptr) {
	char *	(*ft_strmapi)(const char *, char (*)(unsigned, char)) = ptr;
	SET_EXPLICATION("your strmapi does not works");

	SANDBOX_RAISE(
			char	*b = "override this !";
			char	b2[0xF0];
			size_t	size = strlen(b);

			for (size_t i = 0; i < size; i++)
				b2[i] = f_strmapi(i, b[i]);
			b2[size] = 0;
			char	*ret = ft_strmapi(b, f_strmapi);
			if (!strcmp(b2, ret))
				exit(TEST_SUCCESS);
			SET_DIFF(ret, b2);
			exit(TEST_FAILED);
			);
}

void			test_ft_strmapi_free(void *ptr) {
	char *	(*ft_strmapi)(const char *, char (*)(unsigned, char)) = ptr;
	SET_EXPLICATION("your strmapi does not malloc ?");

	SANDBOX_RAISE(
			char	*b = "override this !";
			char	b2[0xF0];
			size_t	size = strlen(b);

			for (size_t i = 0; i < size; i++)
				b2[i] = f_strmapi(i, b[i]);
			b2[size] = 0;
			STDOUT_TO_BUFF;
			char *newstr = ft_strmapi(b, f_strmapi);
			if (!strcmp(newstr, b2))
				exit(TEST_SUCCESS);
			free(newstr);
			write(1, "", 1);
			VOID_STDOUT;
			SET_DIFF(b2, newstr);
			exit(TEST_FAILED);
			);
}

void			test_ft_strmapi_malloc_null(void *ptr) {
	char *	(*ft_strmapi)(const char *, char (*)(unsigned, char)) = ptr;
	SET_EXPLICATION("you did not protect your malloc return");

	SANDBOX_RAISE(
			char	*b = "override this !";

			MALLOC_NULL;
			char *newstr = ft_strmapi(b, f_strmapi);
			MALLOC_RESET;
			if (newstr == NULL)
				exit(TEST_SUCCESS);
			SET_DIFF(NULL, newstr);
			exit(TEST_FAILED);
			);
}

void			test_ft_strmapi_null1(void *ptr) {
	char *	(*ft_strmapi)(const char *, char (*)(unsigned, char)) = ptr;
	SET_EXPLICATION("your strmapi does not segfault when null parameter is sent");

	SANDBOX_KO(
			ft_strmapi(NULL, f_strmapi);
			);
}

void			test_ft_strmapi_null2(void *ptr) {
	char *	(*ft_strmapi)(const char *, char (*)(unsigned, char)) = ptr;
	SET_EXPLICATION("your strmapi does not segfault when null parameter is sent");

	SANDBOX_KO(
			ft_strmapi("olol", NULL);
			ft_strmapi(NULL, NULL);
			);
}
void            test_ft_strmapi(void){
	add_fun_subtest(test_ft_strmapi_basic);
	add_fun_subtest(test_ft_strmapi_free);
	add_fun_subtest(test_ft_strmapi_malloc_null);
	add_fun_subtest(test_ft_strmapi_null1);
	add_fun_subtest(test_ft_strmapi_null2);
}

////////////////////////////////
//         ft_strequ          //
////////////////////////////////

void			test_ft_strequ_basic(void *ptr) {
	int		(*ft_strequ)(const char *s1, const char *s2) = ptr;

	SANDBOX_RAISE(
			char	*s1 = STRING_1;
			char	*s2 = STRING_2;

			int		i1 = ft_strequ(s1, s2);
			if (i1 == 0)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(0, i1);
			exit(TEST_FAILED);
			);
}

void			test_ft_strequ_basic2(void *ptr) {
	int		(*ft_strequ)(const char *s1, const char *s2) = ptr;
	SET_EXPLICATION("your strequ does not works with empty string");

	SANDBOX_RAISE(
			char	*s1 = "";
			char	*s2 = "";

			int		i1 = ft_strequ(s1, s2);
			if (i1 == 1)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(0, i1);
			exit(TEST_FAILED);
			);
}

void			test_ft_strequ_same_pointer(void *ptr) {
	int		(*ft_strequ)(const char *s1, const char *s2) = ptr;
	SET_EXPLICATION("your strequ does not works with empty string");

	SANDBOX_RAISE(
			char	*s1 = "NYANCAT INSIDE";

			int		i1 = ft_strequ(s1, s1);
			if (i1 == 1)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(0, i1);
			exit(TEST_FAILED);
			);
}

void			test_ft_strequ_null1(void *ptr) {
	int		(*ft_strequ)(const char *s1, const char *s2) = ptr;
	SET_EXPLICATION("your strequ does not segfault when null parameter is sent");

	SANDBOX_KO(
			char	*s1 = "AAAAAAAA";

			ft_strequ(NULL, s1);
			);
}

void			test_ft_strequ_null2(void *ptr) {
	int		(*ft_strequ)(const char *s1, const char *s2) = ptr;
	SET_EXPLICATION("your strequ does not segfault when null parameter is sent");

	SANDBOX_KO(
			char	*s1 = "AAAAAAAA";

			ft_strequ(s1, NULL);
			ft_strequ(NULL, NULL);
			);
}

void            test_ft_strequ(void){
	add_fun_subtest(test_ft_strequ_basic);
	add_fun_subtest(test_ft_strequ_basic2);
	add_fun_subtest(test_ft_strequ_same_pointer);
	add_fun_subtest(test_ft_strequ_null1);
	add_fun_subtest(test_ft_strequ_null2);
}

////////////////////////////////
//         ft_strnequ         //
////////////////////////////////

void			test_ft_strnequ_basic(void *ptr) {
	int		(*ft_strnequ)(const char *s1, const char *s2, size_t n) = ptr;

	SANDBOX_RAISE(
			char	*s1 = STRING_1;
			char	*s2 = STRING_2;

			int		i1 = ft_strnequ(s1, s2, strlen(s1));
			if (i1 == 0)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(0, i1);
			exit(TEST_FAILED);
			);
}

void			test_ft_strnequ_basic2(void *ptr) {
	int		(*ft_strnequ)(const char *s1, const char *s2, size_t n) = ptr;
	SET_EXPLICATION("your strnequ does not works with empty string");

	SANDBOX_RAISE(
			char	*s1 = "";
			char	*s2 = "";

			int		i1 = ft_strnequ(s1, s2, 1000);
			if (i1 == 1)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(0, i1);
			exit(TEST_FAILED);
			);
}

void			test_ft_strnequ_same_pointer(void *ptr) {
	int		(*ft_strnequ)(const char *s1, const char *s2, size_t n) = ptr;
	SET_EXPLICATION("your strnequ does not works with empty string");

	SANDBOX_RAISE(
			char	*s1 = "NYANCAT INSIDE";

			int		i1 = ft_strnequ(s1, s1, strlen(s1));
			if (i1 == 1)
				exit(TEST_SUCCESS);
			SET_DIFF_INT(0, i1);
			exit(TEST_FAILED);
			);
}

void			test_ft_strnequ_null1(void *ptr) {
	int		(*ft_strnequ)(const char *s1, const char *s2, size_t n) = ptr;
	SET_EXPLICATION("your strnequ does not segfault when null parameter is sent");

	SANDBOX_KO(
			char	*s1 = "AAAAAAAA";

			ft_strnequ(NULL, s1, 3);
			);
}

void			test_ft_strnequ_null2(void *ptr) {
	int		(*ft_strnequ)(const char *s1, const char *s2, size_t n) = ptr;
	SET_EXPLICATION("your strnequ does not segfault when null parameter is sent");

	SANDBOX_KO(
			char	*s1 = "AAAAAAAA";

			ft_strnequ(s1, NULL, 3);
			ft_strnequ(NULL, NULL, 3);
			);
}

void            test_ft_strnequ(void){
	add_fun_subtest(test_ft_strnequ_basic);
	add_fun_subtest(test_ft_strnequ_basic2);
	add_fun_subtest(test_ft_strnequ_same_pointer);
	add_fun_subtest(test_ft_strnequ_null1);
	add_fun_subtest(test_ft_strnequ_null2);
}

////////////////////////////////
//         ft_strsub          //
////////////////////////////////

//FIXME this function needs a test for \0 at end of the string

void			test_ft_strsub_basic(void *ptr) {
	char	*(*ft_strsub)(const char *, size_t, size_t) = ptr;
	SET_EXPLICATION("your strsub does not works with valid input");

	SANDBOX_RAISE(
			char	*str = "i just want this part #############";
			size_t	size = 22;

			char	*ret = ft_strsub(str, 0, size);
			if (!strncmp(ret, str, size)) {
				free(ret);
				exit(TEST_SUCCESS);
			}
			SET_DIFF("i just want this part", ret);
			free(ret);
			exit(TEST_FAILED);
			);
}

void			test_ft_strsub_basic2(void *ptr) {
	char	*(*ft_strsub)(const char *, size_t, size_t) = ptr;
	SET_EXPLICATION("your strsub does not works with valid input");

	SANDBOX_RAISE(
			char	*str = "i just want this part #############";
			size_t	size = 20;

			char	*ret = ft_strsub(str, 5, size);
			if (!strncmp(ret, str + 5, size)) {
				free(ret);
				exit(TEST_SUCCESS);
			}
			SET_DIFF("t want this part ###", ret);
			free(ret);
			exit(TEST_FAILED);
			);
}

void			test_ft_strsub_out1(void *ptr) {
	char	*(*ft_strsub)(const char *, size_t, size_t) = ptr;
	SET_EXPLICATION("your strsub does not segfault/return null when invalid start/length is sent");

	SANDBOX_KO(
			char	*s = strdup("out of this ???");
			
			char	*ret = ft_strsub(s, 40, 20);
			free(s);
			if (ret == NULL)
				exit(TEST_SUCCESS);
			);
}

void			test_ft_strsub_zero(void *ptr) {
	char	*(*ft_strsub)(const char *, size_t, size_t) = ptr;
	SET_EXPLICATION("your strsub does not set \\0 to the end of the string");

	SANDBOX_RAISE(
			char	str[] = "i just want this part #############";
			size_t	size = 20;

			MALLOC_MEMSET;
			char	*ret = ft_strsub(str, 5, size);
			MALLOC_RESET;
			str[size + 5] = 0;
			if (!memcmp(ret, str + 5, size + 1)) {
				free(ret);
				exit(TEST_SUCCESS);
			}
			SET_DIFF("t want this part ###", ret);
			free(ret);
			exit(TEST_FAILED);
			);
}

void			test_ft_strsub_malloc_null(void *ptr) {
	char	*(*ft_strsub)(const char *, size_t, size_t) = ptr;
	SET_EXPLICATION("you did not protect your malloc");

	SANDBOX_RAISE(
			char	*s = "malloc protection !";

			MALLOC_NULL;
			char	*ret = ft_strsub(s, 0, 5);
			MALLOC_RESET;
			if (ret == NULL)
				exit(TEST_SUCCESS);
			SET_DIFF_PTR(NULL, ret);
			exit(TEST_FAILED);
			(void)s;
			(void)ft_strsub;
			);
}

void			test_ft_strsub_all(void *ptr) {
	char	*(*ft_strsub)(const char *, size_t, size_t) = ptr;
	SET_EXPLICATION("your strsub does not works for a whole string");

	SANDBOX_RAISE(
			char	*s = "all of this !";
			size_t	size = strlen(s);

			char	*ret = ft_strsub(s, 0, size);

			if (!strcmp(s, ret)) {
				free(ret);
				exit(TEST_SUCCESS);
			}
			SET_DIFF(s, ret);
			free(ret);
			exit(TEST_FAILED);
			);
}

void			test_ft_strsub_null(void *ptr) {
	char	*(*ft_strsub)(const char *, size_t, size_t) = ptr;
	SET_EXPLICATION("your strsub does not segfault when null parameter is sent");

	SANDBOX_KO(
			ft_strsub(NULL, 0, 12);
			);
}

void            test_ft_strsub(void){
	add_fun_subtest(test_ft_strsub_basic);
	add_fun_subtest(test_ft_strsub_basic2);
	add_fun_subtest(test_ft_strsub_out1);
	add_fun_subtest(test_ft_strsub_zero);
	add_fun_subtest(test_ft_strsub_malloc_null);
	add_fun_subtest(test_ft_strsub_all);
	add_fun_subtest(test_ft_strsub_null);
}

////////////////////////////////
//         ft_strjoin         //
////////////////////////////////

void			test_ft_strjoin_basic(void *ptr) {
	char *	(*ft_strjoin)(char *, char *) = ptr;
	SET_EXPLICATION("your strjoin does not works with basic input");

	SANDBOX_RAISE(
			char	*s1 = "my favorite animal is";
			char	*s2 = " ";
			char	*s3 = "the nyancat";

			char	*res = ft_strjoin(ft_strjoin(s1, s2), s3);
			if (!strcmp(res, "my favorite animal is the nyancat"))
				exit(TEST_SUCCESS);
			SET_DIFF("my favorite animal is the nyancat", res);
			exit(TEST_FAILED);
			);
}

void			test_ft_strjoin_free(void *ptr) {
	char *	(*ft_strjoin)(char *, char *) = ptr;
	SET_EXPLICATION("your strjoin does not allocate the memory");

	SANDBOX_RAISE(
			char	*s1 = "my favorite animal is";
			char	*s2 = " ";
			char	*s3 = "the nyancat";

			char	*tmp = ft_strjoin(s1, s2);
			char	*res = ft_strjoin(tmp, s3);
			free(tmp);
			if (!strcmp(res, "my favorite animal is the nyancat")) {
				free(res);
				exit(TEST_SUCCESS);
			}
			SET_DIFF("my favorite animal is the nyancat", res);
			free(res);
			exit(TEST_FAILED);
			);
}

void			test_ft_strjoin_overlap(void *ptr) {
	char *	(*ft_strjoin)(char *, char *) = ptr;
	SET_EXPLICATION("your strjoin does not works with overlap input");

	SANDBOX_RAISE(
			char	*s1 = "my favorite animal is ";
			char	*s2 = s1 + 20;

			char	*res = ft_strjoin(s2, s1);
			if (!strcmp(res, "s my favorite animal is "))
				exit(TEST_SUCCESS);
			SET_DIFF("s my favorite animal is ", res);
			exit(TEST_FAILED);
			);
}

void			test_ft_strjoin_malloc_null(void *ptr) {
	char *	(*ft_strjoin)(char *, char *) = ptr;
	SET_EXPLICATION("you did not protect your malloc return");

	SANDBOX_RAISE(
			char	*s1 = "where is my ";
			char	*s2 = "malloc ???";

			MALLOC_NULL;
			char	*res = ft_strjoin(s2, s1);
			MALLOC_RESET;
			if (res == NULL)
				exit(TEST_SUCCESS);
			SET_DIFF_PTR(NULL, res);
			exit(TEST_FAILED);
			);
}

void			test_ft_strjoin_zero(void *ptr) {
	char *	(*ft_strjoin)(char *, char *) = ptr;
	SET_EXPLICATION("your strjoin does not set \\0 to the end of the string");

	SANDBOX_RAISE(
			char	*s1 = "where is my ";
			char	*s2 = "malloc ???";
			char	*s3 = "where is my malloc ???";

			MALLOC_MEMSET;
			char	*res = ft_strjoin(s1, s2);
			MALLOC_RESET;
			if (!strcmp(res, s3))
				exit(TEST_SUCCESS);
			SET_DIFF(s3, res);
			exit(TEST_FAILED);
			);
}

void			test_ft_strjoin_null1(void *ptr) {
	char *	(*ft_strjoin)(char *, char *) = ptr;
	SET_EXPLICATION("your strjoin does not segfault/return null when null parameter is sent");

	SANDBOX_KO(
			char	*s1 = "where is my ";

			char	*res = ft_strjoin(NULL, s1);
			if (res == NULL)
				exit(TEST_SUCCESS);
			SET_DIFF_PTR(NULL, res);
			exit(TEST_FAILED);
			);
}

void			test_ft_strjoin_null2(void *ptr) {
	char *	(*ft_strjoin)(char *, char *) = ptr;
	SET_EXPLICATION("your strjoin does not segfault/return null when null parameter is sent");

	SANDBOX_KO(
			char	*s1 = "where is my ";

			char	*res = ft_strjoin(s1, NULL);
			if (res == NULL)
				exit(TEST_SUCCESS);
			SET_DIFF_PTR(NULL, res);
			exit(TEST_FAILED);
			);
}

void            test_ft_strjoin(void){
	add_fun_subtest(test_ft_strjoin_basic);
	add_fun_subtest(test_ft_strjoin_free);
	add_fun_subtest(test_ft_strjoin_overlap);
	add_fun_subtest(test_ft_strjoin_malloc_null);
	add_fun_subtest(test_ft_strjoin_zero);
	add_fun_subtest(test_ft_strjoin_null1);
	add_fun_subtest(test_ft_strjoin_null2);
}

////////////////////////////////
//         ft_strtrim         //
////////////////////////////////

void			test_ft_strtrim_basic(void *ptr) {
	char *		(*ft_strtrim)(const char *) = ptr;
	SET_EXPLICATION("your strtrim does not works with basic input");

	SANDBOX_RAISE(
			char	*s1 = "   \t  \n\n \t\t  \n\n\nHello \t  Please\n Trim me !\n   \n \n \t\t\n  ";
			char	*s2 = "Hello \t  Please\n Trim me !";

			char	*ret = ft_strtrim(s1);
			if (!strcmp(ret, s2))
				exit(TEST_SUCCESS);
			SET_DIFF(s2, ret);
			exit(TEST_FAILED);
			);
}

void			test_ft_strtrim_basic2(void *ptr) {
	char *		(*ft_strtrim)(const char *) = ptr;
	SET_EXPLICATION("your strtrim does not works with basic input");

	SANDBOX_RAISE(
			char	*s1 = "   \t  \n\n \t\t  \n\n\nHello \t  Please\n Trim me !";
			char	*s2 = "Hello \t  Please\n Trim me !";

			char	*ret = ft_strtrim(s1);
			if (!strcmp(ret, s2))
				exit(TEST_SUCCESS);
			SET_DIFF(s2, ret);
			exit(TEST_FAILED);
			);
}

void			test_ft_strtrim_basic3(void *ptr) {
	char *		(*ft_strtrim)(const char *) = ptr;
	SET_EXPLICATION("your strtrim does not works with basic input");

	SANDBOX_RAISE(
			char	*s1 = "Hello \t  Please\n Trim me !";
			char	*s2 = "Hello \t  Please\n Trim me !";

			char	*ret = ft_strtrim(s1);
			if (!strcmp(ret, s2))
				exit(TEST_SUCCESS);
			SET_DIFF(s2, ret);
			exit(TEST_FAILED);
			);
}

void			test_ft_strtrim_free(void *ptr) {
	char *		(*ft_strtrim)(const char *) = ptr;
	SET_EXPLICATION("your strtrim does not allocate memory");

	SANDBOX_RAISE(
			char	*s1 = "   \t  \n\n \t\t  \n\n\nHello \t  Please\n Trim me !\n   \n \n \t\t\n  ";
			char	*s2 = "Hello \t  Please\n Trim me !";

			char	*ret = ft_strtrim(s1);
			if (!strcmp(ret, s2)) {
				free(ret);
				exit(TEST_SUCCESS);
			}
			SET_DIFF(s2, ret);
			free(ret);
			exit(TEST_FAILED);
			);
}

void			test_ft_strtrim_malloc_null(void *ptr) {
	char *		(*ft_strtrim)(const char *) = ptr;
	SET_EXPLICATION("you dont protect your malloc return");

	SANDBOX_RAISE(
			char	*s1 = "   \t  \n\n \t\t  \n\n\nHello \t  Please\n Trim me !\n   \n \n \t\t\n  ";

			MALLOC_NULL;
			char	*ret = ft_strtrim(s1);
			MALLOC_RESET;
			if (ret == NULL)
				exit(TEST_SUCCESS);
			SET_DIFF_PTR(NULL, ret);
			exit(TEST_FAILED);
			);
}

void			test_ft_strtrim_zero(void *ptr) {
	char *		(*ft_strtrim)(const char *) = ptr;
	SET_EXPLICATION("your strtrim does not set \\0 to the end of the string");

	SANDBOX_RAISE(
			char	*s1 = "   \t  \n\n \t\t  \n\n\nHello \t  Please\n Trim me !\n   \n \n \t\t\n  ";
			char	*s2 = "Hello \t  Please\n Trim me !";

			MALLOC_MEMSET;
			char	*ret = ft_strtrim(s1);
			MALLOC_RESET;
			if (!strcmp(s2, ret)) {
				free(ret);
				exit(TEST_SUCCESS);
			}
			SET_DIFF(ret, s2);
			free(ret);
			exit(TEST_FAILED);
			);
}

void			test_ft_strtrim_null(void *ptr) {
	char *		(*ft_strtrim)(const char *) = ptr;
	SET_EXPLICATION("your strtrim does not segfault/return null when null parameter is sent");

	SANDBOX_KO(
			char	*ret = ft_strtrim(NULL);
			if (!ret)
				exit(TEST_SUCCESS);
			SET_DIFF_PTR(NULL, ret);
			exit(TEST_FAILED);
			);
}

void            test_ft_strtrim(void){
	add_fun_subtest(test_ft_strtrim_basic);
	add_fun_subtest(test_ft_strtrim_basic2);
	add_fun_subtest(test_ft_strtrim_basic3);
	add_fun_subtest(test_ft_strtrim_free);
	add_fun_subtest(test_ft_strtrim_malloc_null);
	add_fun_subtest(test_ft_strtrim_zero);
	add_fun_subtest(test_ft_strtrim_null);
}

////////////////////////////////
//        ft_strsplit         //
////////////////////////////////

void			test_ft_strsplit_basic(void *ptr) {
	char	**(*ft_strsplit)(char *, char) = ptr;
	SET_EXPLICATION("your strsplit does not works with basic input");
	char	**ret = (char*[6]){"split", "this", "for", "me", "!", NULL};

	SANDBOX_RAISE(
			char	*s = "      split       this for   me  !       ";

			char	**r = ft_strsplit(s, ' ');
			while (*r) {
				if (strcmp(*r, *ret)) {
					SET_DIFF(*ret, *r);
					exit(TEST_FAILED);
				}
				r++;
				ret++;
			}
			exit(TEST_SUCCESS);
			);
}

void			test_ft_strsplit_free(void *ptr) {
	char	**(*ft_strsplit)(char *, char) = ptr;
	SET_EXPLICATION("your strsplit does not works with basic input");
	char	**ret = (char*[6]){"split  ", "this", "for", "me", "!", NULL};

	SANDBOX_RAISE(
			char	*s = "split  ||this|for|me|||||!|";
			int		i = 0;

			char	**r = ft_strsplit(s, '|');
			while (r[i]) {
				if (strcmp(r[i], *ret)) {
					SET_DIFF(*ret, r[i]);
					exit(TEST_FAILED);
				}
				free(r[i]);
				i++;
				ret++;
			}
			free(r);
			exit(TEST_SUCCESS);
			);
}

void			test_ft_strsplit_malloc_null(void *ptr) {
	char	**(*ft_strsplit)(char *, char) = ptr;
	SET_EXPLICATION("you did not protect your strsplit");

	SANDBOX_RAISE(
			char	*s = "      split       this for   me  !       ";

			MALLOC_NULL;
			char	**r = ft_strsplit(s, ' ');
			MALLOC_RESET;
			if (!r)
				exit(TEST_SUCCESS);
			SET_DIFF_PTR(NULL, r);
			exit(TEST_FAILED);
			);
}

void			test_ft_strsplit_zero(void *ptr) {
	char	**(*ft_strsplit)(char *, char) = ptr;
	SET_EXPLICATION("your strsplit does not works with basic input");
	char	**ret = (char*[6]){"split", "this", "for", "me", "!", NULL};

	SANDBOX_RAISE(
			char	*s = "      split       this for   me  !       ";

			MALLOC_MEMSET;
			char	**r = ft_strsplit(s, ' ');
			MALLOC_RESET;
			while (*r) {
				if (strcmp(*r, *ret)) {
					SET_DIFF(*ret, *r);
					exit(TEST_FAILED);
				}
				r++;
				ret++;
			}
			exit(TEST_SUCCESS);
			);
}

void			test_ft_strsplit_null(void *ptr) {
	char	**(*ft_strsplit)(char *, char) = ptr;
	SET_EXPLICATION("your strsplit does not segfault/return null when null parameter is sent");

	SANDBOX_KO(
			char	**ret = ft_strsplit(NULL, ' ');
			if (!ret)
				exit(TEST_SUCCESS);
			SET_DIFF_PTR(NULL, ret);
			exit(TEST_FAILED);
			)
}

void            test_ft_strsplit(void){
	add_fun_subtest(test_ft_strsplit_basic);
	add_fun_subtest(test_ft_strsplit_free);
	add_fun_subtest(test_ft_strsplit_malloc_null);
	add_fun_subtest(test_ft_strsplit_zero);
	add_fun_subtest(test_ft_strsplit_null);
}

////////////////////////////////
//         ft_itoa            //
////////////////////////////////

void			test_ft_itoa_basic(void *ptr) {
	char	*(*ft_itoa)(int) = ptr;
	SET_EXPLICATION("your itoa does not works with basic input");

	SANDBOX_RAISE(
			char	*i1 = ft_itoa(-623);
			char	*i2 = ft_itoa(156);
			char	*i3 = ft_itoa(-0);

			if (strcmp(i1, "-623")) {
				SET_DIFF(i1, "-623");
				exit(TEST_FAILED);
			}
			if (strcmp(i2, "156")) {
				SET_DIFF(i2, "156");
				exit(TEST_FAILED);
			}
			if (strcmp(i3, "0")) {
				SET_DIFF(i3, "0");
				exit(TEST_FAILED);
			}
			exit(TEST_SUCCESS);
			);
}

void			test_ft_itoa_random(void *ptr) {
	char	*(*ft_itoa)(int) = ptr;
	SET_EXPLICATION("your itoa does not works with random number");

	SANDBOX_RAISE(
			srand(clock());
			int		n;
			char	*d;

			for (int i = 0; i < 2000; i++) {
				n = rand();
				d = ft_itoa(n);
				if (atoi(d) != n) {
					SET_DIFF_INT(atoi(d), n)
					exit(TEST_FAILED);
				}
			}
			exit(TEST_SUCCESS);
			);
}

void			test_ft_itoa_max_int(void *ptr) {
	char	*(*ft_itoa)(int) = ptr;
	SET_EXPLICATION("your itoa does not works with max int");

	SANDBOX_RAISE(
			char	*i1 = ft_itoa(INT_MAX);

			if (atoi(i1) != INT_MAX) {
				SET_DIFF(i1, "0");
				exit(TEST_FAILED);
			}
			exit(TEST_SUCCESS);
			);
}

void			test_ft_itoa_min_int(void *ptr) {
	char	*(*ft_itoa)(int) = ptr;
	SET_EXPLICATION("your itoa does not works with min int");

	SANDBOX_RAISE(
			char	*i1 = ft_itoa(INT_MIN);

			if (atoi(i1) != INT_MIN) {
				SET_DIFF(i1, "0");
				exit(TEST_FAILED);
			}
			exit(TEST_SUCCESS);
			);
}

void			test_ft_itoa_zero_byte(void *ptr) {
	char	*(*ft_itoa)(int) = ptr;
	SET_EXPLICATION("your itoa don't set \\0 at the end of the string");

	SANDBOX_RAISE(
			MALLOC_MEMSET;
			char	*i1 = ft_itoa(-1234);
			MALLOC_RESET;

			if (strcmp(i1, "-1234")) {
				SET_DIFF(i1, "-1234");
				exit(TEST_FAILED);
			}
			exit(TEST_SUCCESS);
			);
}

void			test_ft_itoa_malloc_null(void *ptr) {
	char	*(*ft_itoa)(int) = ptr;
	SET_EXPLICATION("your itoa don't set \\0 at the end of the string");

	SANDBOX_RAISE(
			MALLOC_NULL;
			char	*i1 = ft_itoa(-1234);
			MALLOC_RESET;

			if (!i1)
				exit(TEST_SUCCESS);
			SET_DIFF(NULL, i1);
			exit(TEST_FAILED);
			);
}

void            test_ft_itoa(void){
	add_fun_subtest(test_ft_itoa_basic);
	add_fun_subtest(test_ft_itoa_random);
	add_fun_subtest(test_ft_itoa_max_int);
	add_fun_subtest(test_ft_itoa_min_int);
	add_fun_subtest(test_ft_itoa_zero_byte);
	add_fun_subtest(test_ft_itoa_malloc_null);
}

////////////////////////////////
//         ft_putchar         //
////////////////////////////////

void			test_ft_putchar_basic(void *ptr) {
	typeof(putchar)	*ft_putchar = ptr;
	SET_EXPLICATION("your putchar does not works with basic input");

	SANDBOX_RAISE(
			char	buff[10];
			char	c = 'o';
			STDOUT_TO_BUFF;
			ft_putchar(c);
			GET_STDOUT(buff, 10);
			if (buff[0] == c)
				exit(TEST_SUCCESS);
			SET_DIFF(buff, &c);
			exit(TEST_FAILED);
			);
}

void			test_ft_putchar_ascii(void *ptr) {
	typeof(putchar)	*ft_putchar = ptr;
	SET_EXPLICATION("your putchar does not works with all ascii chars");

	SANDBOX_RAISE(
			char	buff[200];
			char	buff2[200];
			STDOUT_TO_BUFF;
			for (int i = 0; i < 128; i++) {
				ft_putchar(i);
				buff2[i] = i;
			}
			GET_STDOUT(buff, 1000);
			for (int i = 0; i < 128; i++)
				if (buff[i] != buff2[i]) {
					SET_DIFF(buff2 + 1, buff + 1);
					exit(TEST_FAILED);
				}
			exit(TEST_SUCCESS);
			);
}

int     nbr_bits(unsigned int nbr)
{
	int     i;

	i = 1;
	while ((nbr = nbr >> 1))
		i++;
	return (i);
}

void    putwchart(int wchar, int *len, char *buff)
{
	unsigned int    ch;
	int             n;
	int				i = 0;

	ch = (unsigned int)wchar;
	n = nbr_bits(ch);
	if (n > 7 && ((*len += 1)))
	{
		if (n > 11 && ((*len += 1)))
		{
			if (n > 16 && ((*len += 2)))
			{
				buff[i++] = ((ch >> 18) & 7) | 240;
				buff[i++] = ((ch >> 12) & 63) | 128;
			}
			else if ((*len += 1))
				buff[i++] = ((ch >> 12) & 15) | 224;
			buff[i++] = ((ch >> 6) & 63) | 128;
		}
		else if ((*len += 1))
			buff[i++] = ((ch >> 6) & 31) | 192;
		buff[i++] = (ch & 63) | 128;
	}
	else if ((*len += 1))
		buff[i++] = ch;
}

void			test_ft_putchar_unicode(void *ptr) {
	typeof(putchar)	*ft_putchar = ptr;
	SET_EXPLICATION("your putchar does not works with unicode");

	SANDBOX_RAISE(
			char	buff[10];
			char	buff2[10];
			int		c = L'ø';
			int		len = 0;
			putwchart(c, &len, buff2);
			buff2[len] = 0;
			STDOUT_TO_BUFF;
			ft_putchar(c);
			GET_STDOUT(buff, 10);
			if (!strcmp(buff, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff, buff2);
			exit(TEST_KO);
			);
	(void)ft_putchar;
}

void            test_ft_putchar(void){
	add_fun_subtest(test_ft_putchar_basic);
	add_fun_subtest(test_ft_putchar_ascii);
	add_fun_subtest(test_ft_putchar_unicode);
}

////////////////////////////////
//         ft_putstr          //
////////////////////////////////

void			test_ft_putstr_basic(void *ptr) {
	void		(*ft_putstr)(const char *) = ptr;
	SET_EXPLICATION("your putstr does not works with basic input");

	SANDBOX_RAISE(
			char	*buff1 = STRING_1;
			char	buff2[0xF00];

			STDOUT_TO_BUFF;
			ft_putstr(buff1);
			write(1, "", 1);
			GET_STDOUT(buff2, sizeof(buff2));
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_putstr_ascii(void *ptr) {
	void		(*ft_putstr)(const char *) = ptr;
	SET_EXPLICATION("your putstr does not works with non ascii chars");

	SANDBOX_RAISE(
			char	*buff1 = "string \x01 of \x63 non \x0a ascii \x12 chars\x1d";
			char	buff2[0xF00];

			STDOUT_TO_BUFF;
			ft_putstr(buff1);
			write(1, "", 1);
			GET_STDOUT(buff2, sizeof(buff2));
			if (!strcmp(buff1, buff2))
				exit(TEST_SUCCESS);
			SET_DIFF(buff1, buff2);
			exit(TEST_FAILED);
			);
}

int     ft_putwstr(wchar_t *wstr, char *buff)
{
	int     len;
	int     ret;
	int     i;

	len = 0;
	ret = 0;
	i = 0;
	if (wstr != NULL)
		while (wstr[i])
		{
			putwchart(wstr[i], &len, buff);
			ret += len;
			i++;
		}
	else
	{
		strcat(buff, "(null)");
		ret = 6;
	}
	return (ret);
}

void			test_ft_putstr_unicode(void *ptr) {
	void		(*ft_putstr)(const char *) = ptr;
	SET_EXPLICATION("your putstr does not works with non ascii chars");

	SANDBOX_RAISE(
			wchar_t	*buff1 = L"よくやった";
			wchar_t	buff2[0xF00];

//			STDOUT_TO_BUFF;
			ft_putstr((char*)buff1);
			write(1, "", 1);
//			GET_STDOUT((char*)buff2, sizeof(buff2));
			if (!strcmp((char*)buff1, (char*)buff2))
				exit(TEST_SUCCESS);
			SET_DIFF((char*)buff1, (char*)buff2);
			exit(TEST_FAILED);
			);
}

void			test_ft_putstr_null(void *ptr) {
	void		(*ft_putstr)(const char *) = ptr;
	SET_EXPLICATION("your putstr does not segfault/print something when null parameter is sent");

	SANDBOX_IRAISE(
			char	buff2[0xF00] = {0};

			STDOUT_TO_BUFF;
			ft_putstr(NULL);
			GET_STDOUT(buff2, sizeof(buff2));
			if (buff2[0])
				exit(TEST_SUCCESS);
			SET_DIFF("(null)", buff2);
			exit(TEST_FAILED);
			);
}

void            test_ft_putstr(void){
	add_fun_subtest(test_ft_putstr_basic);
	add_fun_subtest(test_ft_putstr_ascii);
//	add_fun_subtest(test_ft_putstr_unicode);
	add_fun_subtest(test_ft_putstr_null);
}

////////////////////////////////
//         ft_putendl         //
////////////////////////////////

void            test_ft_putendl(void){ }

////////////////////////////////
//         ft_putnbr          //
////////////////////////////////

void            test_ft_putnbr(void){ }

////////////////////////////////
//       ft_putchar_fd        //
////////////////////////////////

void            test_ft_putchar_fd(void){ }

////////////////////////////////
//       ft_putstr_fd         //
////////////////////////////////

void            test_ft_putstr_fd(void){ }

////////////////////////////////
//       ft_putendl_fd        //
////////////////////////////////

void            test_ft_putendl_fd(void){ }

////////////////////////////////
//       ft_putnbr_fd         //
////////////////////////////////

void            test_ft_putnbr_fd(void){ }




////////////////////////////////
//        ft_lstnew           //
////////////////////////////////

void			test_ft_lstnew_basic(void *ptr) {
	t_list	*(*ft_lstnew)(const void *, size_t) = ptr;
	SET_EXPLICATION("your lstnew does not works with basic input");

	SANDBOX_RAISE(
			char	*data = "hello, i'm a data";
			t_list	*l = ft_lstnew(data, strlen(data) + 1);

			if (!strcmp(data, l->content))
				exit(TEST_SUCCESS);
			SET_DIFF(data, l->content);
			exit(TEST_FAILED);
			);
}

void			test_ft_lstnew_free(void *ptr) {
	t_list	*(*ft_lstnew)(const void *, size_t) = ptr;
	SET_EXPLICATION("your lstnew does not allocate memory");

	SANDBOX_RAISE(
			char	*data = "hello, i'm a data";
			t_list	*l = ft_lstnew(data, strlen(data) + 1);

			if (!strcmp(data, l->content)) {
				free(l->content);
				free(l);
				exit(TEST_SUCCESS);
			}
			SET_DIFF(data, l->content);
			exit(TEST_FAILED);
			);
}

void			test_ft_lstnew_null(void *ptr) {
	t_list	*(*ft_lstnew)(const void *, size_t) = ptr;
	SET_EXPLICATION("your lstnew does not works with null parameter");

	SANDBOX_RAISE(
			t_list	*l = ft_lstnew(NULL, 0);

			if (!l->content)
				exit(TEST_SUCCESS);
			SET_DIFF_PTR(NULL, l->content);
			exit(TEST_FAILED);
			);
}

void			test_ft_lstnew_malloc_null(void *ptr) {
	t_list	*(*ft_lstnew)(const void *, size_t) = ptr;
	SET_EXPLICATION("your malloc return is not protected");

	SANDBOX_RAISE(
			char	*data = "hello, i'm a data";

			MALLOC_NULL;
			t_list	*l = ft_lstnew(data, strlen(data) + 1);
			MALLOC_RESET;
			if (!l)
				exit(TEST_SUCCESS);
			SET_DIFF_PTR(NULL, l);
			exit(TEST_FAILED);
			);
}

void			test_ft_lstnew(void){
	printf("OK !\n");
	add_fun_subtest(test_ft_lstnew_basic);
	add_fun_subtest(test_ft_lstnew_free);
	add_fun_subtest(test_ft_lstnew_null);
	add_fun_subtest(test_ft_lstnew_malloc_null);
}

////////////////////////////////
//        ft_lstdelone        //
////////////////////////////////

void			lstdelone_f(void *d, size_t n) {
	free(d);
	(void)n;
}

t_list			*lstnew(void *d, size_t s) {
	t_list *ret = malloc(sizeof(t_list));

	ret->next = NULL;
	ret->content = d;
	ret->content_size = s;
	return (ret);
}

void			test_ft_lstdelone_basic(void *ptr) {
	void		(*ft_lstdelone)(t_list **, void (*)(void *, size_t)) = ptr;
	SET_EXPLICATION("your lstdelone does not works");

	SANDBOX_RAISE(
			t_list	*l = lstnew(malloc(10), 10);

			ft_lstdelone(&l, lstdelone_f);
			if (!l)
				exit(TEST_SUCCESS);
			SET_DIFF_PTR(NULL, l);
			exit(TEST_FAILED);
			);
}

void			test_ft_lstdelone(void) {
	add_fun_subtest(test_ft_lstdelone_basic);
}


////////////////////////////////
//         ft_lstdel          //
////////////////////////////////

void			test_ft_lstdel(void){ }

////////////////////////////////
//        ft_lstadd           //
////////////////////////////////

void			test_ft_lstadd(void){ }

////////////////////////////////
//        ft_lstiter           //
////////////////////////////////

void			test_ft_lstiter(void){ }

////////////////////////////////
//         ft_lstmap          //
////////////////////////////////

void			test_ft_lstmap(void){ }

////////////////////////////////
//         ft_islower         //
////////////////////////////////

void			test_ft_islower_(void *ptr) {
	typeof(islower)	*ft_islower = ptr;
	SET_EXPLICATION("your islower does not works ...");

	SANDBOX_RAISE(
			for (int i = -50; i < 530; i++) {
				if (ft_islower(i) != islower(i)) {
					SET_DIFF_INT(islower(i), ft_islower(i));
					exit(TEST_FAILED);
				}
			}
			exit(TEST_SUCCESS);
			);
}

void			test_ft_islower(void){
	add_fun_subtest(test_ft_islower_);
}

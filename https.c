#include <stdio.h>
#include <curl/curl.h>
size_t test( void *buffer, size_t size, size_t nmemb, FILE *file)
{
  int i=0;
  printf("Hello, World! \n");
  size_t r_size = fwrite(buffer, size, nmemb, file);
  return r_size;
}

int main(void)
{
  CURL *curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.baidu.com/");

#ifdef SKIP_PEER_VERIFICATION
    /*
	 * 如果要连接到不使用由CA捆绑包中的某个证书签名的证书的站点，可以跳过对服务器
	 * 证书的验证。这使得连接更加不安全。
     * 如果您将服务器的CA证书存储在默认捆绑包以外的其他地方，那么CURLOPT_CAPATH
	 * 选项可能会很方便。
	 */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    /*
	 * 如果您要连接的站点使用的主机名与他们在服务器证书的commonName（或
	 * subjectAltName）字段中提到的不同，libcurl将拒绝连接。您可以跳过此
	 * 检查，但这会降低连接的安全性。
	 */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

	char url[] = "http://www.sina.com.cn";
    char path[] = "save_file.txt";
    FILE *file = fopen(path, "w");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, test);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
	/* 执行请求，res将获得返回代码 */
    res = curl_easy_perform(curl);
	
	fclose(file);
    /* 检查错误 */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));   //返回中文错误提示(curl中文错误码)

    /* 总是清理 */
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  return 0;
}

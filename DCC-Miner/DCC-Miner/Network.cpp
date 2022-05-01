
#include <iostream>
#include <string>
#include <vector>
#include "Console.cpp"
#include <Urlmon.h>
#include <curl/curl.h>
#include <cpr/cpr.h>
using namespace std;


class Http
{
public:
	string blockVersion = "";

	string StartHttpWebRequest(string URL, vector<string> args_vals)
	{
		string html = "";

		string url = URL;
		for (int i = 0; i < args_vals.size(); i++)
		{
			if (i > 0)
				url += "&";
			url += args_vals.at(i);
		}
		if (blockVersion != "")
			url += "&Version=" + blockVersion;
		
		auto response = cpr::Get(cpr::Url{ url });
		html = response.text;

		Console().WriteLine(html, Console().Debug());

		return html;
	}
};

int DownloadFile(string url, string saveAs) {
	CURL* curl;
	FILE* fp;
	CURLcode res;
	curl = curl_easy_init();
	if (curl)
	{
		fp = fopen(saveAs.c_str(), "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
	}
	return 0;
}
int DownloadFile(string url, string saveAs, bool printStatus) {
	CURL* curl;
	FILE* fp;
	CURLcode res;
	curl = curl_easy_init();
	if (curl)
	{
		if (printStatus)
			Console().Write("Downloading from: \"" + url + "\" ...\r", Console().Network());
		fp = fopen(saveAs.c_str(), "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
		if (printStatus)
			Console().Write("Downloading from: \"" + url + "\" Done\n", Console().Network());
	}
	return 0;
}

string UploadFile(string url, string filePath)
{
	cpr::Response r = cpr::Post(cpr::Url{ url },
		cpr::Multipart{ {"file", cpr::File{filePath}} });
	//std::cout << r.text << std::endl;

	return r.text;

	//CURL* curl;
	//CURLcode res;

	//curl_httppost* post = NULL;
	//curl_httppost* last = NULL;
	///*HttpPost* post = NULL;
	//HttpPost* last = NULL;*/

	//curl = curl_easy_init();
	//if (curl)
	//{
	//	curl_formadd(&post, &last,
	//		CURLFORM_COPYNAME, "filename",
	//		CURLFORM_COPYCONTENTS, "programOutData",
	//		CURLFORM_END);
	//	curl_formadd(&post, &last,
	//		CURLFORM_COPYNAME, "file",
	//		CURLFORM_FILE, filePath,
	//		CURLFORM_END);

	//	curl_easy_setopt(curl, CURLOPT_URL, url);
	//	curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);

	//	res = curl_easy_perform(curl);
	//	if (res)
	//	{
	//		return 0;
	//	}

	//	curl_formfree(post);
	//}
	//else
	//{
	//	return 0;
	//}

	//curl_easy_cleanup(curl);
}
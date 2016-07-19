/*
 * PackageLicenseDeclared: Apache-2.0
 * Copyright (c) 2015 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"
#include "errno.h"
#include "ublox/HTTPClient.h"


static void blinky(void) {
    static DigitalOut led(LED1);
    led = !led;
    printf("LED = %d \n\r",led.read());
}

static void get(void) {
	char resultBuffer[128];
	HTTPClient* http = NULL;
	http = HTTPClient::getInstance();

    int ret = http->get("http://mbed.org/media/uploads/donatien/hello.txt", resultBuffer, 128);
    if (!ret){
    	printf("Page fetched successfully - read %d characters \r\n",  strlen(resultBuffer));
    	printf("Result: %s \r\n", resultBuffer);
    }
    else{
    	printf("ret:%d resultBuffer:%s responseCode:%d \r\n\n",  ret, resultBuffer, http->getHTTPResponseCode());
    }
}

static void post(void) {
	char resultBuffer[128];
	HTTPClient* http = NULL;
	http = HTTPClient::getInstance();

	HTTPMap map;
	HTTPText text(resultBuffer, 128);
    map.put("Hello", "World");
    map.put("test", "1234");

    int ret = http->post("http://httpbin.org/post", map, &text);
    if (!ret){
      printf("Executed POST successfully - read %d characters \r\n",  strlen(resultBuffer));
      printf("Result: %s\n", resultBuffer);
	}
    else{
      printf("Error - ret = %d - HTTP return code = %d \r\n",  ret, http->getHTTPResponseCode());
    }
}


int main(void)
{

    while (true)
    {
    	//blinky();
    	get();
    	//post();
    	wait(30);
    }

    return -1;
}

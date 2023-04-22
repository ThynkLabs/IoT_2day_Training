/*
  Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
  Permission is hereby granted, free of charge, to any person obtaining a copy of this
  software and associated documentation files (the "Software"), to deal in the Software
  without restriction, including without limitation the rights to use, copy, modify,
  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <pgmspace.h>

#define THINGNAME "group_1"

const char WIFI_SSID[] = "JAYSH";
const char WIFI_PASSWORD[] = "1111111111";
const char AWS_IOT_ENDPOINT[]= "aynomhw2tgffs-ats.iot.ap-south-1.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAPOvpzVttyjKvXrQqZ/UYrWiBDYSMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMzA0MTMwODA2
MjdaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQD6JaPX+YW5Cb+XVvMe
MbnLg+46lCK7JqL7S7ONes1D0wrmxJer0q/W5+PupHMhqGE+0ueFZ5BKy+lkvIAs
LGJmnXvo7QSkVmatnUl8WThPKdZ7NuflA7ILoCx70kgfG4QhISuiUNYZ1K/SUA2q
Utwr9vbB0ggf0yr3MwJu5K09fXCp9xnRH+QUm/KDxQOe1UnEDU55ShagviV8mDGg
c2hyS+gs/BI2wxdmMXCeQz7dYvjdBON0YX2FVmuvr/DHm7iroqNCkDg8/KiZ0tZY
in8vSY6dzTTTSeLwHpiX7XDE0tinMBDju7GLQMSwog3mUKluDohzrVCB0yhn9Yya
NbLVAgMBAAGjYDBeMB8GA1UdIwQYMBaAFHKzjw6JdwyRAZY9q+37QQEkj9xTMB0G
A1UdDgQWBBQeCTRXmRb/sv88vfBI4EsqJpFN7DAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAKAHh9HqdrViI7SyBd6NyeKiW
g3ITNl30DBV78wcC7qUcB4PaWqEmSzuVWRxfhaY4NbejA1sio0zbvsEeteNs856W
gMZV9dOTyEFZX40cvaJLDyyIbKEYfx8iU0cxBzojRomVRRSjsek/7lcOOsYVrSWZ
tthOI5iMDSe92887O83wBwiXg3iv/PKQ3nmhR5+9HaIim827lVs7e+sYoDqv6fo3
3U4/UjBz7ber/99eEZtjeHbaRbECTivd6YwS2LBs1enegZDUc7b8W3j8n/xL2KQN
c6qy3r693Gr4maF1ZtULIwZ1XrhMuYx0cKxmKBZPR8A452XtNB3OzkTQlcqpQg==
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEA+iWj1/mFuQm/l1bzHjG5y4PuOpQiuyai+0uzjXrNQ9MK5sSX
q9Kv1ufj7qRzIahhPtLnhWeQSsvpZLyALCxiZp176O0EpFZmrZ1JfFk4TynWezbn
5QOyC6Ase9JIHxuEISErolDWGdSv0lANqlLcK/b2wdIIH9Mq9zMCbuStPX1wqfcZ
0R/kFJvyg8UDntVJxA1OeUoWoL4lfJgxoHNockvoLPwSNsMXZjFwnkM+3WL43QTj
dGF9hVZrr6/wx5u4q6KjQpA4PPyomdLWWIp/L0mOnc0000ni8B6Yl+1wxNLYpzAQ
47uxi0DEsKIN5lCpbg6Ic61QgdMoZ/WMmjWy1QIDAQABAoIBADmuREGg//zTCqLT
IexsevM60MwhLIELP7nCkvykvIBPQcxEuNSeGH3tqtl0gjfYo9PgvhI890DIFGFu
Nf/5nBcdaV0kilV6tuKBylgqGpnmg9aVqpNcbsnPfXJv4sGJjsY05+Ld0QDT0lck
roH/6VUZ9Xxr+gOcpeOql30KrgfnWEayuyo7deVovYptboVRQfS6vz5a/9C9iPrB
laLA+6IwEMb5b27nwgRIv3X739D0ODILsx5KZT6lsLmdSspMfLexA9YbkQzAVVP/
EfLsasBpj10PTfruRqyJmhLNjKWmE1MFtGKC/l6eefWfJvgWq3u+DjEiZjmrgDHz
8shZWmECgYEA/d+pr0ctD3G7ZRr1VSuLu75UQ2ru2MHVM3jNvGFHWH6IbQ0RP3MA
LQtH5rRfyH3C+Qk2gah4qR/p/Z8vu7pgxZb2lPHQPy1h+Hu1Cf8dencOP7ANr1Sr
BkvxJ8oZWVgpCQ/wEw18qpCQplvaZCLvPFN9XK0XS11qg83fbWf4ORcCgYEA/D38
nSPJ5qVW8rnNfz4H+YZjdjwf6g4dxQRKHNA0FdyG2kbo8/YwZrIBdmuGqt/Cia6b
eVfx/DjJizadrSFvaboL8gGdkJGLvtDuISbnbwWtSR/p41+DmEp1J67vnJZ+SsLe
1S1C8US8cO4JLYC+eApHR2+SPIBmCVZkGhvxzvMCgYAspBuuWpGt2Y3eJXNmWpXj
mYAvqqn9K3hV6LQkn+ZvxTAwHNAfnBU31nf6NVVyZ8rVB62x9vHgq1/13PwDwq4p
kHYjkrHPqidEDlyzOUzxr+WthUOixPydytTI7lyuvTXaBhdtAj4dr/X/ir9IRGxU
60lr9nPWKMMGEjlrf5DCWQKBgQDulCax7p7SBALIVAtVVbOvRHgg5d99vtpTdaov
tJH/N3VpUXaXAX1oNOeDPVLDnh7foQI29ILSAFhIz2C115EMnEceIH8KtU9LLUx+
mNB/xwvOxVuwjq/mRE6pOSIzpnhPeB/R3BycHVprKgoOOt5spbQjkhjsFrnsDQVj
WJkPFwKBgQCaSy+AfzrltYM1snShxyVPMZAW0p2YXI/JPMLq1HpfwLIgqWdwg/qG
DIednqqHtmzHUjzTf1X80Fg629Oipoo1A20UrYQvTQZglV7svAAucCgDml1y7OOF
93Xhh/VMiADHvc6boAwJT7ELwWUr96x0viz/IW6/a6M7+0Rh6efFGA==
-----END RSA PRIVATE KEY-----
)KEY";

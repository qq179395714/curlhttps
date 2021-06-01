# curlhttps
wget https://curl.se/download/curl-7.77.0.tar.gz
tar xvzf curl-7.77.0.tar.gz
cd curl-7.77.0
./configure --disable-static --enable-shared --without-libidn --without-ssl --without-librtmp --without-gnutls --without-nss --without-libssh2 --without-zlib --without-winidn --disable-rtsp --disable-ldap --disable-ldaps --disable-ipv6
make //成功后将在“lib/.libs”目录下生成动态库
make install //安装curl
cd /curl-7.77.0/docs/examples
`curl-config --cc` -o https https.c `curl-config --cflags --libs`
./https

克隆
git clone https://github.com/qq179395714/curlhttps.git

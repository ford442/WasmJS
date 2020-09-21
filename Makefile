EMCC = em++ -O3 --closure 1 --bind -Iinclude
EM_SOURCE_PATH = $(PWD)/emsdk

NGX_PREFIX_PATH = $(PWD)/build
NGX_SOURCE_PATH = $(PWD)/nginx
NGX_GCC_OPT = "-O3 -march=native"
NGX_CONFIGURE = ./auto/configure 	--without-select_module \
					--without-poll_module \
					--without-http_charset_module \
					--without-http_ssi_module \
					--without-http_userid_module \
					--without-http_access_module \
					--without-http_auth_basic_module \
					--without-http_mirror_module \
					--without-http_autoindex_module \
					--without-http_geo_module \
					--without-http_map_module \
					--without-http_split_clients_module \
					--without-http_referer_module \
					--without-http_rewrite_module \
					--without-http_fastcgi_module \
					--without-http_proxy_module \
					--without-http_uwsgi_module \
					--without-http_scgi_module \
					--without-http_grpc_module \
					--without-http_memcached_module \
					--without-http_limit_conn_module \
					--without-http_limit_req_module \
					--without-http_empty_gif_module \
					--without-http_browser_module \
					--without-http_upstream_hash_module \
					--without-http_upstream_ip_hash_module \
					--without-http_upstream_least_conn_module \
					--without-http_upstream_random_module \
					--without-http_upstream_keepalive_module \
					--without-http_upstream_zone_module \
					--without-http_gzip_module \
					--without-http-cache \
					--without-mail_pop3_module \
					--without-mail_imap_module \
					--without-mail_smtp_module \
					--without-stream_limit_conn_module \
					--without-stream_access_module \
					--without-stream_geo_module \
					--without-stream_map_module \
					--without-stream_split_clients_module \
					--without-stream_return_module \
					--without-stream_upstream_hash_module \
					--without-stream_upstream_least_conn_module \
					--without-stream_upstream_random_module \
					--without-stream_upstream_zone_module \
					--without-pcre \
					--prefix=$(NGX_PREFIX_PATH) \
					--with-cc-opt=$(NGX_CC_OPT) \
					#--with-http_v2_module \
					#--with-http_ssl_module \

all:
	$(EMCC) source/console.cpp examples/console.cpp -o build/public_html/js/console.js
	$(EMCC) -DWJS_DEBUG source/console.cpp source/dom.cpp examples/dom.cpp -o build/public_html/js/dom.js
	$(EMCC) -DWJS_DEBUG source/console.cpp source/indexed_db.cpp examples/indexed_db.cpp -o build/public_html/js/indexed_db.js

console:
	$(EMCC) source/console.cpp examples/console.cpp -o build/public_html/js/console.js

console_debug:
	$(EMCC) -DWJS_DEBUG source/console.cpp examples/console.cpp -o build/public_html/js/console.js

dom:
	$(EMCC) source/dom.cpp examples/dom.cpp -o build/public_html/js/dom.js

dom_debug:
	$(EMCC) -DWJS_DEBUG source/console.cpp source/dom.cpp examples/dom.cpp -o build/public_html/js/dom.js

indexed_db:
	$(EMCC) source/console.cpp source/indexed_db.cpp examples/indexed_db.cpp -o build/public_html/js/indexed_db.js

indexed_db_debug:
	$(EMCC) -DWJS_DEBUG source/console.cpp source/indexed_db.cpp examples/indexed_db.cpp -o build/public_html/js/indexed_db.js

emscripten_install:
	$(EM_SOURCE_PATH)/emsdk install latest
	$(EM_SOURCE_PATH)/emsdk activate latest

nginx_build:
	$(MAKE) -j `nproc` -C $(NGX_SOURCE_PATH)

nginx_clean:
	$(MAKE) clean -C $(NGX_SOURCE_PATH)

nginx_configure:
	cd $(NGX_SOURCE_PATH) && $(NGX_CONFIGURE)

#define ZERO(x) memset(&x, 0, sizeof(x))

#define NEWBUF_(_ptr_, _len_, _newlen_) {\
  free(_ptr_); \
  _len_ = (_newlen_); \
  if(_newlen_ > 0) { \
    _ptr_ = calloc(sizeof(*(_ptr_)), (_len_)); \
  } else { \
    _ptr_ = NULL; \
  } \
}
#define GROWBUF_(_ptr_, _len_) {\
  long _newlen_ = _len_ > 0 ? _len_*2 : 32; \
  void * _newbuf_ = calloc(sizeof(*(_ptr_)), (_newlen_)); \
  memcpy(_newbuf_, _ptr_, sizeof(*(_ptr_))*_len_); \
  free(_ptr_); \
  _ptr_ = _newbuf_; \
  _len_ = _newlen_; \
}
#define FREEBUF_(_ptr_, _len_) {\
  free(_ptr_); \
  _ptr_ = NULL; \
  _len_ = 0; \
}

#define BUF(_T_) struct { _T_ * elem; long len; }

#define NEWBUF(_str_, _newlen_)   NEWBUF_ (_str_.elem, _str_.len, _newlen_)
#define GROWBUF(_str_)            GROWBUF_(_str_.elem, _str_.len)
#define FREEBUF(_str_)            FREEBUF_(_str_.elem, _str_.len)

#define BUFLEN(_str_) (_str_.len)
#define BUFSIZE(_str_) (sizeof(*(_str_.elem))*_str_.len)

#define BUFEACH(_str_, _name_) for(__typeof__(_name)

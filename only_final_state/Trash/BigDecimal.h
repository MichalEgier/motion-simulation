#define BigDecimal int*
,int length_of_first,int length_of_second
BigDecimal add(BigDecimal x,BigDecimal y,int length_of_first,int length_of_second);

BigDecimal subtraction(BigDecimal minuend,BigDecimal subtrahend,int length_of_first,int length_of_second);

BigDecimal multiply(BigDecimal x,BigDecimal y,int length_of_first,int length_of_second);

BigDecimal divide(BigDecimal dividend,BigDecimal divider,int length_of_first,int length_of_second);

BigDecimal intToBigDecimal(int argument);

int bigDecimalToInt(BigDecimal argument);



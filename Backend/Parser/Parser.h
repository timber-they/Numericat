#include "Function.h"

#ifndef BACKEND_PARSER_H
#define BACKEND_PARSER_H

/// Returns NULL when something goes wrong
/// Remember to free the result of this method, if not NULL
/// raw should be a null terminated string
Function parseFunction(char *raw);
int validateDyck(char *in);

#endif //BACKEND_PARSER_H

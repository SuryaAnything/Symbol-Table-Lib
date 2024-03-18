#include <stdio.h>
#include "symbol.h"

int main(void) {

    begin
        assign(Integer,"a","34");
        assign(String,"b","Surya");
        begin
            assign(String, "b", "23");
            assign(String, "c", "21.45");
            Fields *field = fetch("b");
            printf("%s",field->stringValue);
        end
    end
}
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <munit/munit.h>

#include <echidna.h>
#include <ll.h>
#include <macros.h>
#include <runtime.h>
#include <symbol.h>

#include <suite.h>


struct _TEST_VALUES {

    uint8_t B1;

    uint8_t B2;
};

//  xxd -i src/boolean.txt

static char _Source[] = {

    0x50, 0x52, 0x4f, 0x47, 0x52, 0x41, 0x4d, 0x20, 
    0x74, 0x65, 0x73, 0x74, 0x0a, 0x56, 0x41, 0x52, 
    0x20, 0x6f, 0x6e, 0x3a, 0x20, 0x42, 0x4f, 0x4f, 
    0x4c, 0x20, 0x3a, 0x3d, 0x20, 0x74, 0x72, 0x75, 
    0x65, 0x3b, 0x20, 0x45, 0x4e, 0x44, 0x5f, 0x56, 
    0x41, 0x52, 0x0a, 0x56, 0x41, 0x52, 0x20, 0x6f, 
    0x66, 0x66, 0x3a, 0x20, 0x42, 0x4f, 0x4f, 0x4c, 
    0x20, 0x3a, 0x3d, 0x20, 0x66, 0x61, 0x6c, 0x73, 
    0x65, 0x3b, 0x20, 0x45, 0x4e, 0x44, 0x5f, 0x56, 
    0x41, 0x52, 0x0a, 0x56, 0x41, 0x52, 0x20, 0x63, 
    0x6f, 0x75, 0x6e, 0x74, 0x3a, 0x20, 0x55, 0x4c, 
    0x49, 0x4e, 0x54, 0x20, 0x3a, 0x3d, 0x20, 0x30, 
    0x3b, 0x20, 0x45, 0x4e, 0x44, 0x5f, 0x56, 0x41, 
    0x52, 0x0a, 0x0a, 0x41, 0x44, 0x44, 0x20, 0x63, 
    0x6f, 0x75, 0x6e, 0x74, 0x2c, 0x20, 0x31, 0x0a, 
    0x53, 0x54, 0x20, 0x63, 0x6f, 0x75, 0x6e, 0x74, 
    0x0a, 0x4c, 0x45, 0x20, 0x31, 0x30, 0x0a, 0x4a, 
    0x4d, 0x50, 0x43, 0x4e, 0x20, 0x65, 0x6e, 0x64, 
    0x0a, 0x0a, 0x4c, 0x44, 0x20, 0x63, 0x6f, 0x75, 
    0x6e, 0x74, 0x0a, 0x4d, 0x4f, 0x44, 0x20, 0x32, 
    0x0a, 0x45, 0x51, 0x20, 0x31, 0x0a, 0x53, 0x20, 
    0x6f, 0x66, 0x66, 0x0a, 0x52, 0x20, 0x6f, 0x6e, 
    0x0a, 0x52, 0x45, 0x54, 0x43, 0x0a, 0x0a, 0x4c, 
    0x44, 0x20, 0x74, 0x72, 0x75, 0x65, 0x0a, 0x52, 
    0x20, 0x6f, 0x66, 0x66, 0x0a, 0x53, 0x20, 0x6f, 
    0x6e, 0x0a, 0x52, 0x45, 0x54, 0x0a, 0x0a, 0x65, 
    0x6e, 0x64, 0x3a, 0x20, 0x5f, 0x65, 0x78, 0x69, 
    0x74, 0x0a, 0x0a, 0x45, 0x4e, 0x44, 0x5f, 0x50, 
    0x52, 0x4f, 0x47, 0x52, 0x41, 0x4d, 0x0a, 0x0a, 
    0x43, 0x4f, 0x4e, 0x46, 0x49, 0x47, 0x55, 0x52, 
    0x41, 0x54, 0x49, 0x4f, 0x4e, 0x20, 0x63, 0x6f, 
    0x6e, 0x66, 0x69, 0x67, 0x31, 0x0a, 0x54, 0x41, 
    0x53, 0x4b, 0x20, 0x74, 0x61, 0x73, 0x6b, 0x31, 
    0x20, 0x28, 0x50, 0x52, 0x49, 0x4f, 0x52, 0x49, 
    0x54, 0x59, 0x20, 0x3a, 0x3d, 0x20, 0x31, 0x29, 
    0x3b, 0x0a, 0x50, 0x52, 0x4f, 0x47, 0x52, 0x41, 
    0x4d, 0x20, 0x70, 0x72, 0x6f, 0x67, 0x72, 0x61, 
    0x6d, 0x31, 0x3a, 0x20, 0x74, 0x65, 0x73, 0x74, 
    0x3b, 0x0a, 0x45, 0x4e, 0x44, 0x5f, 0x43, 0x4f, 
    0x4e, 0x46, 0x49, 0x47, 0x55, 0x52, 0x41, 0x54, 
    0x49, 0x4f, 0x4e, 0x0a, 0x00
};

static int _Cycle = 0;

static struct _TEST_VALUES _Values[] = {
    { 0, 1 },
    { 1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, 1 },
    { 1, 0 },
};


static void
_test_boolean_callback(ECHIDNA *Context, void *Arg, void *User) {
    RUNTIME *pRun;
    RUNTIME_CONTEXT *pContext;
    SYMBOL *pSymbol;
    VALUE sValue;
    struct _TEST_VALUES *pValue;

    /* Arg == &RUNTIME_CONTEXT.Stats */
    munit_assert_not_null(Arg);
    munit_assert_not_null(pContext = container_of(Arg, RUNTIME_CONTEXT, Stats));
    munit_assert_not_null(pRun = (RUNTIME *) pContext->Parent);
    munit_assert_int(_Cycle, >=, 0);
    if(_Cycle >= 10)
        return;

    pValue = &_Values[_Cycle];
    munit_assert_not_null(pSymbol = symbol_search(Context, "config1", "__Single", "program1", "on"));
    value_copy(&sValue, &pSymbol->Value);
    memcpy((char *) &sValue.Value.Pointer, &pRun->Memory[pSymbol->Offset], sValue.Length);
    munit_assert_uint32(sValue.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sValue.Value.B1, ==, pValue->B1);

    munit_assert_not_null(pSymbol = symbol_search(Context, "config1", "__Single", "program1", "off"));
    value_copy(&sValue, &pSymbol->Value);
    memcpy((char *) &sValue.Value.Pointer, &pRun->Memory[pSymbol->Offset], sValue.Length);
    munit_assert_uint32(sValue.Type, ==, TYPE_BOOL);
    munit_assert_uint8(sValue.Value.B1, ==, pValue->B2);

    ++_Cycle;
}


MunitResult 
test_operator_boolean(const MunitParameter Parameters[], void *Fixture) {
    ECHIDNA *pContext;

    pContext = (ECHIDNA *) Fixture;
    munit_assert_not_null(pContext);

    munit_assert_int(test_parse(pContext, _Source), ==, 0);
    pContext->Option |= (OPTION_COMPILE | OPTION_RUN);
    pContext->Output = NULL;
    munit_assert_int(echidna_compile(pContext), ==, 0);
    munit_assert_int(echidna_callback(pContext, CALLBACK_CYCLE_FINISH, NULL, _test_boolean_callback), ==, 0);
    _Cycle = 0;
    munit_assert_int(echidna_run(pContext), ==, 0);
    munit_assert_int(_Cycle, ==, 10);

    return MUNIT_OK;
}



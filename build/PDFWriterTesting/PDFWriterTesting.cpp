#include <ctype.h>  /* NOLINT */
#include <stdio.h>  /* NOLINT */
#include <stdlib.h> /* NOLINT */
#include <string.h> /* NOLINT */
#include <time.h>   /* NOLINT */

#if defined(_MSC_VER)
#pragma warning(disable : 4996) /* deprecation */
#endif



/* Forward declare test functions. */
int AppendAndReplaceURLAnnotations(int, char*[]);
int AppendingAndReading(int, char*[]);
int AppendPagesTest(int, char*[]);
int AppendSpecialPagesTest(int, char*[]);
int AppendWithAnnotations(int, char*[]);
int BasicModification(int, char*[]);
int BoxingBaseTest(int, char*[]);
int BufferedOutputStreamTest(int, char*[]);
int CIDSetWritingCFF(int, char*[]);
int CIDSetWritingTrueType(int, char*[]);
int CIDSetWritingTrueType2(int, char*[]);
int ColorEmojiColr(int, char*[]);
int ColorEmojiColrV1(int, char*[]);
int CopyingAndMergingEmptyPages(int, char*[]);
int CustomLogTest(int, char*[]);
int DCTDecodeFilterTest(int, char*[]);
int DFontTest(int, char*[]);
int EmptyFileTest(int, char*[]);
int EmptyPagesPDF(int, char*[]);
int EncryptedPDF(int, char*[]);
int FlateEncryptionTest(int, char*[]);
int FlateObjectDecodeTest(int, char*[]);
int FormXObjectTest(int, char*[]);
int FreeTypeInitializationTest(int, char*[]);
int HighLevelContentContext(int, char*[]);
int HighLevelImages(int, char*[]);
int ImagesAndFormsForwardReferenceTest(int, char*[]);
int InputFlateDecodeTester(int, char*[]);
int InputImagesAsStreamsTest(int, char*[]);
int JpegLibTest(int, char*[]);
int JPGImageTest(int, char*[]);
int LinksTest(int, char*[]);
int LogTest(int, char*[]);
int MergePDFPages(int, char*[]);
int MergeToPDFForm(int, char*[]);
int ModifyingEncryptedFile(int, char*[]);
int ModifyingExistingFileContent(int, char*[]);
int OpenTypeTest(int, char*[]);
int OutputFileStreamTest(int, char*[]);
int PageModifierTest(int, char*[]);
int PageOrderModification(int, char*[]);
int ParsingBadXref(int, char*[]);
int ParsingFaulty(int, char*[]);
int PDFCopyingContextTest(int, char*[]);
int PDFDateTest(int, char*[]);
int PDFEmbedTest(int, char*[]);
int PDFObjectCastTest(int, char*[]);
int PDFObjectParserTest(int, char*[]);
int PDFParserTest(int, char*[]);
int PDFWithPassword(int, char*[]);
int PFBStreamTest(int, char*[]);
int PNGImageTest(int, char*[]);
int RecryptPDF(int, char*[]);
int RefCountTest(int, char*[]);
int RotatedPagesPDF(int, char*[]);
int ShutDownRestartTest(int, char*[]);
int SimpleContentPageTest(int, char*[]);
int SimpleTextUsage(int, char*[]);
int TestMeasurementsTest(int, char*[]);
int TextUsageBugs(int, char*[]);
int TIFFImageTest(int, char*[]);
int TiffSpecialsTest(int, char*[]);
int TimerTest(int, char*[]);
int TrueTypeTest(int, char*[]);
int TTCTest(int, char*[]);
int Type1Test(int, char*[]);
int UnicodeTextUsage(int, char*[]);
int UppercaseSequanceTest(int, char*[]);
int WatermarkTest(int, char*[]);
int WatermarkWithContextOpacityTest(int, char*[]);


#ifdef __cplusplus
#  define CM_CAST(TYPE, EXPR) static_cast<TYPE>(EXPR)
#  if __cplusplus >= 201103L
#    define CM_NULL nullptr
#  else
#    define CM_NULL NULL
#  endif
#  define CM_NAMESPACE_BEGIN namespace {
#  define CM_NAMESPACE_END }
#  define CM_LOCAL
#else
#  define CM_CAST(TYPE, EXPR) (TYPE)(EXPR)
#  define CM_NULL NULL
#  define CM_NAMESPACE_BEGIN
#  define CM_NAMESPACE_END
#  define CM_LOCAL static
#endif

CM_NAMESPACE_BEGIN

/* Create map.  */

typedef int (*MainFuncPointer)(int, char* []); /* NOLINT */
typedef struct /* NOLINT */
{
  const char* name;
  MainFuncPointer func;
} functionMapEntry;

CM_LOCAL const functionMapEntry cmakeGeneratedFunctionMapEntries[] = {
    {
    "AppendAndReplaceURLAnnotations",
    AppendAndReplaceURLAnnotations
  },
  {
    "AppendingAndReading",
    AppendingAndReading
  },
  {
    "AppendPagesTest",
    AppendPagesTest
  },
  {
    "AppendSpecialPagesTest",
    AppendSpecialPagesTest
  },
  {
    "AppendWithAnnotations",
    AppendWithAnnotations
  },
  {
    "BasicModification",
    BasicModification
  },
  {
    "BoxingBaseTest",
    BoxingBaseTest
  },
  {
    "BufferedOutputStreamTest",
    BufferedOutputStreamTest
  },
  {
    "CIDSetWritingCFF",
    CIDSetWritingCFF
  },
  {
    "CIDSetWritingTrueType",
    CIDSetWritingTrueType
  },
  {
    "CIDSetWritingTrueType2",
    CIDSetWritingTrueType2
  },
  {
    "ColorEmojiColr",
    ColorEmojiColr
  },
  {
    "ColorEmojiColrV1",
    ColorEmojiColrV1
  },
  {
    "CopyingAndMergingEmptyPages",
    CopyingAndMergingEmptyPages
  },
  {
    "CustomLogTest",
    CustomLogTest
  },
  {
    "DCTDecodeFilterTest",
    DCTDecodeFilterTest
  },
  {
    "DFontTest",
    DFontTest
  },
  {
    "EmptyFileTest",
    EmptyFileTest
  },
  {
    "EmptyPagesPDF",
    EmptyPagesPDF
  },
  {
    "EncryptedPDF",
    EncryptedPDF
  },
  {
    "FlateEncryptionTest",
    FlateEncryptionTest
  },
  {
    "FlateObjectDecodeTest",
    FlateObjectDecodeTest
  },
  {
    "FormXObjectTest",
    FormXObjectTest
  },
  {
    "FreeTypeInitializationTest",
    FreeTypeInitializationTest
  },
  {
    "HighLevelContentContext",
    HighLevelContentContext
  },
  {
    "HighLevelImages",
    HighLevelImages
  },
  {
    "ImagesAndFormsForwardReferenceTest",
    ImagesAndFormsForwardReferenceTest
  },
  {
    "InputFlateDecodeTester",
    InputFlateDecodeTester
  },
  {
    "InputImagesAsStreamsTest",
    InputImagesAsStreamsTest
  },
  {
    "JpegLibTest",
    JpegLibTest
  },
  {
    "JPGImageTest",
    JPGImageTest
  },
  {
    "LinksTest",
    LinksTest
  },
  {
    "LogTest",
    LogTest
  },
  {
    "MergePDFPages",
    MergePDFPages
  },
  {
    "MergeToPDFForm",
    MergeToPDFForm
  },
  {
    "ModifyingEncryptedFile",
    ModifyingEncryptedFile
  },
  {
    "ModifyingExistingFileContent",
    ModifyingExistingFileContent
  },
  {
    "OpenTypeTest",
    OpenTypeTest
  },
  {
    "OutputFileStreamTest",
    OutputFileStreamTest
  },
  {
    "PageModifierTest",
    PageModifierTest
  },
  {
    "PageOrderModification",
    PageOrderModification
  },
  {
    "ParsingBadXref",
    ParsingBadXref
  },
  {
    "ParsingFaulty",
    ParsingFaulty
  },
  {
    "PDFCopyingContextTest",
    PDFCopyingContextTest
  },
  {
    "PDFDateTest",
    PDFDateTest
  },
  {
    "PDFEmbedTest",
    PDFEmbedTest
  },
  {
    "PDFObjectCastTest",
    PDFObjectCastTest
  },
  {
    "PDFObjectParserTest",
    PDFObjectParserTest
  },
  {
    "PDFParserTest",
    PDFParserTest
  },
  {
    "PDFWithPassword",
    PDFWithPassword
  },
  {
    "PFBStreamTest",
    PFBStreamTest
  },
  {
    "PNGImageTest",
    PNGImageTest
  },
  {
    "RecryptPDF",
    RecryptPDF
  },
  {
    "RefCountTest",
    RefCountTest
  },
  {
    "RotatedPagesPDF",
    RotatedPagesPDF
  },
  {
    "ShutDownRestartTest",
    ShutDownRestartTest
  },
  {
    "SimpleContentPageTest",
    SimpleContentPageTest
  },
  {
    "SimpleTextUsage",
    SimpleTextUsage
  },
  {
    "TestMeasurementsTest",
    TestMeasurementsTest
  },
  {
    "TextUsageBugs",
    TextUsageBugs
  },
  {
    "TIFFImageTest",
    TIFFImageTest
  },
  {
    "TiffSpecialsTest",
    TiffSpecialsTest
  },
  {
    "TimerTest",
    TimerTest
  },
  {
    "TrueTypeTest",
    TrueTypeTest
  },
  {
    "TTCTest",
    TTCTest
  },
  {
    "Type1Test",
    Type1Test
  },
  {
    "UnicodeTextUsage",
    UnicodeTextUsage
  },
  {
    "UppercaseSequanceTest",
    UppercaseSequanceTest
  },
  {
    "WatermarkTest",
    WatermarkTest
  },
  {
    "WatermarkWithContextOpacityTest",
    WatermarkWithContextOpacityTest
  },

  { CM_NULL, CM_NULL } /* NOLINT */
};

CM_LOCAL const int NumTests = CM_CAST(int,
  sizeof(cmakeGeneratedFunctionMapEntries) / sizeof(functionMapEntry)) - 1;

/* Allocate and create a lowercased copy of string
   (note that it has to be free'd manually) */
CM_LOCAL char* lowercase(const char* string)
{
  char *new_string;
  char *p;
  size_t stringSize;

  stringSize = CM_CAST(size_t, strlen(string) + 1);
  new_string = CM_CAST(char*, malloc(sizeof(char) * stringSize));

  if (new_string == CM_NULL) { /* NOLINT */
    return CM_NULL;            /* NOLINT */
  }
  strcpy(new_string, string);  /* NOLINT */
  for (p = new_string; *p != 0; ++p) {
    *p = CM_CAST(char, tolower(*p));
  }
  return new_string;
}

CM_LOCAL int isTestSkipped(const char *name, int n_skipped_tests, char *skipped_tests[]) {
  int i;
  for (i = 0; i < n_skipped_tests; i++) {
    if (strcmp(name, skipped_tests[i]) == 0) {
      return 1;
    }
  }

  return 0;
}

CM_NAMESPACE_END

int main(int ac, char* av[])
{
  int i;
  int testNum = 0;
  int partial_match;
  int run_all;
  char *arg;
  int testToRun = -1;

  

  /* If no test name was given */
  /* process command line with user function.  */
  if (ac < 2) {
    /* Ask for a test.  */
    printf("Available tests:\n");
    for (i = 0; i < NumTests; ++i) {
      printf("%3d. %s\n", i, cmakeGeneratedFunctionMapEntries[i].name);
    }
    printf("To run a test, enter the test number: ");
    fflush(stdout);
    if (scanf("%d", &testNum) != 1) {
      printf("Couldn't parse that input as a number\n");
      return -1;
    }
    if (testNum >= NumTests) {
      printf("%3d is an invalid test number.\n", testNum);
      return -1;
    }
    testToRun = testNum;
    ac--;
    av++;
  }
  partial_match = 0;
  run_all = 0;
  arg = CM_NULL; /* NOLINT */
  /* If partial match or running all tests are requested.  */
  if (testToRun == -1 && ac > 1) {
    partial_match = (strcmp(av[1], "-R") == 0) ? 1 : 0;
    run_all = (strcmp(av[1], "-A") == 0) ? 1 : 0;
  }
  if (partial_match != 0 && ac < 3) {
    printf("-R needs an additional parameter.\n");
    return -1;
  }
  if (run_all == 1) {
    clock_t t;
    int status = 0;
    const char* status_message = CM_NULL;
    printf("TAP version 13\n");
    printf("1..%d\n", NumTests);
    for (i = 0; i < NumTests; ++i) {
      const char *name = cmakeGeneratedFunctionMapEntries[i].name;
      if (ac > 2) {
        if (isTestSkipped(name, ac - 2, av + 2) == 1) {
          printf("ok %d %s # SKIP\n", i + 1, name);
          continue;
        }
      }
      t = clock();
      status = (*cmakeGeneratedFunctionMapEntries[i].func)(ac, av);
      t = clock() - t;
      status_message = (status == -1) ? "not ok" : "ok";
      {
        double time_taken = CM_CAST(double, t) / CLOCKS_PER_SEC;
        printf("%s %d %s # %f\n", status_message, i + 1, name, time_taken);
      }
    }
    printf("All tests finished.\n");

    return 0;
  }

  if (testToRun == -1) {
    arg = lowercase(av[1 + partial_match]);
  }
  for (i = 0; i < NumTests && testToRun == -1; ++i) {
    char *test_name = lowercase(cmakeGeneratedFunctionMapEntries[i].name);
    if (partial_match != 0 && strstr(test_name, arg) != CM_NULL) { /* NOLINT */
      testToRun = i;
      ac -= 2;
      av += 2;
    } else if (partial_match == 0 && strcmp(test_name, arg) == 0) {
      testToRun = i;
      ac--;
      av++;
    }
    free(test_name);
  }
  free(arg);
  if (testToRun != -1) {
    int result;

    if (testToRun < 0 || testToRun >= NumTests) {
      printf("testToRun was modified by TestDriver code to an invalid value: "
             "%3d.\n",
             testNum);
      return -1;
    }
    result = (*cmakeGeneratedFunctionMapEntries[testToRun].func)(ac, av);

    return result;
  }

  /* Nothing was run, display the test names.  */
  printf("Available tests:\n");
  for (i = 0; i < NumTests; ++i) {
    printf("%3d. %s\n", i, cmakeGeneratedFunctionMapEntries[i].name);
  }
  printf("Failed: %s is an invalid test name.\n", av[1]);

  return -1;
}

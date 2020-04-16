#include <clang-c/Index.h>

#include <iostream>
#include <string>

std::string getFileName( CXFile file )
{
  const char *c;
  std::string result;
  CXString filename  = clang_getFileName( file );
  c = clang_getCString( filename );
  if (c == NULL) {result == "";}
  else {result = c;}

  clang_disposeString( filename );
  return result;
}

std::string getCursorKindName( CXCursorKind cursorKind )
{
  const char *c;
  std::string result;
  CXString kindName  = clang_getCursorKindSpelling( cursorKind );
  c = clang_getCString( kindName );
  if (c == NULL) {result == "";}
  else {result = c;}

  clang_disposeString( kindName );
  return result;
}

std::string getCursorSpelling( CXCursor cursor )
{
  const char *c;
  std::string result;
  CXString cursorSpelling = clang_getCursorSpelling( cursor );
  c = clang_getCString( cursorSpelling );
  if (c == NULL) {result == "";}
  else {result = c;}

  clang_disposeString( cursorSpelling );
  return result;
}

CXChildVisitResult visitor( CXCursor cursor, CXCursor /* parent */, CXClientData clientData )
{

  CXSourceLocation location = clang_getCursorLocation( cursor );
  if( clang_Location_isInSystemHeader( location ) != 0 )
    return CXChildVisit_Continue;

  CXFile file;
  unsigned line=0;

  clang_getSpellingLocation(location, &file, &line, NULL, NULL);

  CXCursor cursorParent = clang_getCursorSemanticParent(cursor);
//  CXCursor cursorParent = clang_getCursorLexicalParent(cursor);
  CXCursorKind cursorKind = clang_getCursorKind( cursor );
  CXCursorKind cursorParentKind = clang_getCursorKind( cursorParent );

  unsigned int curLevel  = *( reinterpret_cast<unsigned int*>( clientData ) );
  unsigned int nextLevel = curLevel + 1;

  std::cout << std::string( curLevel, '-' ) << " " << getCursorKindName(cursorKind ) << " (" <<
  getCursorSpelling( cursor ) << ") <" << getCursorSpelling( cursorParent ) << ", " << getCursorKindName(cursorParentKind)
  << "> [" << getFileName(file) << ":" << std::to_string(line) << "] "  << "\n";

  clang_visitChildren( cursor,
                       visitor,
                       &nextLevel ); 

  return CXChildVisit_Continue;
}

int main( int argc, char** argv )
{
  if( argc < 2 )
    return -1;

  CXIndex index        = clang_createIndex( 0, 0 );
  CXTranslationUnit tu = clang_parseTranslationUnit(
    index,
    argv[1], nullptr, 0,
    nullptr, 0,
//    CXTranslationUnit_None  );
    CXTranslationUnit_DetailedPreprocessingRecord  );


  if( !tu )
  {
    std::cerr << "Unable to parse translation unit. Quitting." << std::endl;
    return -1;
  }


  CXCursor rootCursor  = clang_getTranslationUnitCursor( tu );

  unsigned int treeLevel = 0;

  clang_visitChildren( rootCursor, visitor, &treeLevel );

  clang_disposeTranslationUnit( tu );
  clang_disposeIndex( index );

  return 0;
}



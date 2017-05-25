#define ITEMS 100

#include <iostream>
#include <sstream>
#include <map>
#include <ctime>

#include "../ListMap.h"

#define TEST_MAP ListMap

static int errCnt = 0;
#define ERR(x) for(;++errCnt;) cout << "\nERR " << x << ": "
#define MSG cout << "\nMSG   : "

using namespace std;

void wyswietl(ListMap *l){
}

int Test2()
{
  cout << "Testy lab liniowe 2-kier" << endl;

  TEST_MAP *DA, *DA1, *DA2, *DA3;
  TEST_MAP::Key i,j,key,key_10,check;
  TEST_MAP::Val val_str;

  /* ---------------------------------------------------------------------------------------------------------*/
  /* ERR 01,02,03,04,05                                                                                       */

  for (i=1;i<=ITEMS;i++)
  {
    DA1=new TEST_MAP;
    MSG << "Wstawiam i sprawdzam "<< i << " elementow.";
    for (key=1;key<=i;key++)
    {
      val_str = to_string( key );
      DA1->insert( make_pair(key,val_str) );
	  for (check=1;check<=ITEMS;check++)
      {
        if (check<=key)
        {
		  if ((DA1->find(check)!=DA1->end())==false)
            ERR(1) << "Nie znalazlem elementu "
                   << "(i="<< i << ", key="<< key <<", check=" << check << ")";
          val_str = to_string(check);
          if( (DA1->find(check))==DA1->end() || DA1->find(check)->second != val_str )
            ERR(2) << "Odczytano zla wartosc "
                   << "(i="<< i << ", key="<< key <<", check=" << check << ")";
        }
        else
        {
          if ((DA1->find(check)!=DA1->end())==true)
            ERR(3) << "Znalazlem element, ktorego nie powinno byc "
                   << "(i="<< i << ", key="<< key <<", check=" << check << ")";
          if ( DA1->find(check)!= DA1->end() )
            ERR(4) << "Slownik nie powinien zawierac tej pary "
                   << "(i="<< i << ", key="<< key <<", check=" << check << ")";
        }
      }
    }
    delete DA1;
    if (CCount::getCount()>0) ERR(5) << "Nie zwolniono calej pamieci";
  }


  /* ---------------------------------------------------------------------------------------------------------*/
  /* ERR 10,11,13,14                                                                                          */

  for (i=1;i<=ITEMS;i++)
  {
    DA1=new TEST_MAP;
    cout << "\nMSG   : Wstawiam i zmieniam "<< i << " elementow.";
    for (key=1;key<=i;key++)
    {
      val_str = to_string(key);
      DA1->insert( make_pair(key,val_str) );

    }
    for (key=1;key<=i;key++)
    {
      key_10=key+10;
      val_str = to_string(key_10);
      (*DA1)[key] = val_str;

      for (check=1;check<=i;check++)
      {
        if (check<=key)
        {
          if ((DA1->find(check)!=DA1->end())==false)
            ERR(10) << "Nie znalazlem elementu "
                    << "(i="<< i << ", key="<< key <<", check=" << check << ")";

          key_10=check+10;
          val_str = to_string(key_10);
          if( DA1->find(check)==DA1->end() || DA1->find(check)->second != val_str )
            ERR(11) << "Odczytano zla wartosc "
                    << "(i="<< i << ", key="<< key <<", check=" << check << ")";
        }
        else
        {
          val_str = to_string(check);
          if( DA1->find(check)==DA1->end() || DA1->find(check)->second != val_str )
            ERR(13) << "Odczytano zla wartosc "
                    << "(i="<< i << ", key="<< key <<", check=" << check << ")";
        }
      }
    }
    delete DA1;
    if (CCount::getCount()>0) ERR(14) << "Nie zwolniono calej pamieci";
  }

  /* ---------------------------------------------------------------------------------------------------------*/
  /* ERR 21,22,23,24,25,26                                                                                    */

  for (i=1;i<=ITEMS;i++)
  {
    cout << "\nMSG   : Wstawiam i kasuje " << i << " elementow.";
    for (j=1;j<=i;j++)
    {
      DA1=new TEST_MAP;
      for (key=1;key<=i;key++)
      {
		val_str = to_string(key);
		(*DA1)[key] = val_str;
	  }
	  DA1->erase(j);
      if( (DA1->find(j)!=DA1->end())==true)
        ERR(21) << "Znalazlem element, ktorego nie powinno byc "
				<< "(i="<< i << ", key="<< key <<", check=" << check << ")" << "j = " << j;

      for (check=1;check<=ITEMS;check++)
      {
        if (check<=i && check!=j)
        {
          if ((DA1->find(check)!=DA1->end())==false)
            ERR(22) << "Nie znalazlem elementu "
                    << "(i="<< i << ", key="<< key <<", check=" << check << ")";
          val_str = to_string(check);
		  if( DA1->find(check)==DA1->end() || DA1->find(check)->second != val_str )
            ERR(23) <<  "Odczytano zla wartosc "
					<< "(i="<< i << ", key="<< key <<", check=" << check << ")";
		}
        else
        {
          if ((DA1->find(check)!=DA1->end())==true)
            ERR(24) << "Znalazlem element, ktorego nie powinno byc "
                    << "(i="<< i << ", key="<< key <<", check=" << check << ")";
          if( DA1->find(check)!=DA1->end() )
            ERR(25) << "Odczytana wartosc powinna byc pusta "
                    << "(i="<< i << ", key="<< key <<", check=" << check << ")";
        }
      }
      delete DA1;
      if (CCount::getCount()>0)
        ERR(26) << "Nie zwolniono calej pamieci";
    }
  }

  /* ---------------------------------------------------------------------------------------------------------*/
  /* ERR 31,32,33,34                                                                                          */

  cout << "\nMSG   : Porownanie pustych slownikow.";
  DA1=new TEST_MAP;
  DA3=new TEST_MAP;
  if (DA1->info_eq(*DA1)==false) ERR(31) << "Slownik powinien byc informacyjnie rowny sam ze soba";
  if (DA1->struct_eq(*DA1)==false) ERR(32) << "Slownik powinien byc strukturalnie rowny sam ze soba";

  if (DA1->info_eq(*DA3)==false) ERR(33) << "Puste slowniki powinny byc informacyjnie rowne";
  if (DA1->struct_eq(*DA3)==false) ERR(34) << "Puste slowniki powinny byc strukturalnie rowne";
  delete DA1;

  /* ---------------------------------------------------------------------------------------------------------*/
  /* ERR 35,36,37,38,39,40,41,42,43,44,46,47,45                                                               */

  DA3->insert( make_pair<int,string>(10,"10") );
  DA3->insert(make_pair<int,string>(11,"11") );

  for (i=1;i<=ITEMS;i++)
  {
    cout << "\nMSG   : Wstawiam i porownuje " << i << "elementow.";
    DA1=new TEST_MAP;
    for (key=1;key<=i;key++)
    {
      val_str = to_string(key);
      //DA1->insert( make_pair(key,val_str) );
      (*DA1)[key] = val_str;
    }
    DA2=new TEST_MAP(*DA1);
    if (DA1->info_eq(*DA1)==false) ERR(35) << "Slownik powinien byc i. rowny sam ze soba, i="<<i;
    if (DA1->struct_eq(*DA1)==false) ERR(36) << "Slownik powinien byc s. rowny sam ze soba, i="<<i;

    if (DA1->info_eq(*DA2)==false) ERR(37) << "Slowniki powinny byc i. rowne, i="<<i;
    if (DA1->struct_eq(*DA2)==false) ERR(38) << "Slowniki powinny byc s. rowne, i="<<i;

    if (DA2->info_eq(*DA1)==false) ERR(39) << "Slowniki powinny byc i. rowne, i="<<i;
    if (DA2->struct_eq(*DA1)==false) ERR(40) << "Slowniki powinny byc s. rowne, i="<<i;

    for (check=1;check<=ITEMS;check++)
    {
      if (check<=i)
      {
        if ((DA2->find(check)!=DA2->end())==false)
          ERR(41) << "Nie znalazlem elementu "
                  << "(i="<< i << ", check=" << check << ")";
        val_str = to_string(check);
        if( DA2->find(check)==DA2->end() || DA2->find(check)->second != val_str )
          ERR(42) << "Odczytano zla wartosc "
                  << "(i="<< i << ", check=" << check << ")";
      }
      else
      {
        if ((DA2->find(check)!=DA2->end())==true)
          ERR(43) << "Znalazlem element, ktorego nie powinno byc "
                  << "(i="<< i << ", check=" << check << ")";
        if ( DA2->find(check)!= DA2->end() )
          ERR(44) << "Odczytana wartosc powinna byc pusta "
                  << "(i="<< i << ", check=" << check << ")";
      }
    }

    if (DA1->info_eq(*DA3)==true) ERR(46) << "Slowniki powinny byc i. rozne, i="<<i;
    if (DA1->struct_eq(*DA3)==true) ERR(47) << "Slowniki powinny byc s. rozne, i="<<i;

    delete DA1;
    delete DA2;
  }
  delete DA3;
  if (CCount::getCount()>0) ERR(45) << "Nie zwolniono calej pamieci";

  /* ---------------------------------------------------------------------------------------------------------*/
  /* ERR 48, 80, 81, 82, 83, 84                                                        */

  cout << "\nMSG   : Wstawiam i porownuje inf.";
  DA1=new TEST_MAP;
  for (key=1;key<=ITEMS;key++)
  {
    val_str = to_string(key);
    DA1->insert( make_pair(key,val_str) );
  }
  DA2=new TEST_MAP;
  for (key=ITEMS;key>=1;key--)
  {
    val_str = to_string(key);
    DA2->insert(make_pair(key,val_str));
  }

  if (DA1->info_eq(*DA2)==false)
    ERR(48) << "Slowniki powinny byc i. rowne";

  cout << "\nMSG   : Czyszcze slownik i porownuje inf.";
  DA1->clear();
  if (DA1->size() != 0 || !DA1->empty())
    ERR(80) << "Slownik powinien byc pusty";
  if (DA1->info_eq(*DA2))
    ERR(81) << "Slowniki powinny byc inf. rozne";
  if (DA1->struct_eq(*DA2))
    ERR(82) << "Slowniki powinny byc strukt. rozne";

  cout << "\nMSG   : Czyszcze oba slownik i porownuje inf.";
  DA2->clear();
  if (!DA1->info_eq(*DA2))
    ERR(81) << "Slowniki powinny byc inf. rowne";
  if (!DA1->struct_eq(*DA2))
    ERR(82) << "Slowniki powinny byc strukt. rowne";

  delete DA1;
  delete DA2;

  /* ---------------------------------------------------------------------------------------------------------*/
  /* ERR 51,52,53,54,55,56,57,58,59,60                                                                        */

  for (i=1;i<=ITEMS;i++)
  {
    cout << "\nMSG   : Wstawiam i przypisuje "<<i<<" elementow.";
    DA1=new TEST_MAP;
    DA2=new TEST_MAP;
    for (key=1;key<=i;key++)
    {
      val_str = to_string(key);
      DA1->insert( make_pair(key,val_str) );
    }

#ifdef OPERATOR_PRZYPISANIA
    *DA2=*DA1;


    if (DA1->info_eq(*DA2)==false) ERR(51) << "Slowniki powinny byc i. rowne, i="<<i;
    if (DA2->info_eq(*DA1)==false) ERR(52) << "Slowniki powinny byc i. rowne, i="<<i;

    for (check=1;check<=ITEMS;check++)
    {
      if (check<=i)
      {
        if ((DA2->find(check)!=DA2->end())==false)
          ERR(53) << "Nie znalazlem elementu "
                  << "(i="<< i << ", check=" << check << ")";
        val_str = to_string(check);
        if( DA2->find(check)==DA2->end() || DA2->find(check)->second != val_str )
          ERR(54) << "Odczytano zla wartosc "
                  << "(i="<< i << ", check=" << check << ")";
      }
      else
      {
        if ((DA2->find(check)!=DA2->end())==true)
          ERR(55) << "Znalazlem element, ktorego nie powinno byc "
                  << "(i="<< i << ", check=" << check << ")";
        if ( DA2->find(check)!= DA2->end() )
          ERR(56) << "Odczytana wartosc powinna byc pusta "
                  << "(i="<< i << ", check=" << check << ")";
      }
    }

    *DA1=*DA1;

    for (check=1;check<=ITEMS;check++)
    {
      if (check<=i)
      {
        if ((DA1->find(check)!=DA1->end())==false)
          ERR(57) << "Nie znalazlem elementu "
                  << "(i="<< i << ", check=" << check << ")";
        val_str = to_string(check);
        if( DA1->find(check)==DA1->end() || DA1->find(check)->second != val_str )
          ERR(58) << "Odczytano zla wartosc "
                  << "(i="<< i << ", check=" << check << ")";
      }
      else
      {
        if ((DA1->find(check)!=DA1->end())==true)
          ERR(59) << "Znalazlem element, ktorego nie powinno byc "
                  << "(i="<< i << ", key="<< key <<", check=" << check << ")";
        if ( DA1->find(check)!= DA1->end() )
          ERR(60) << "Odczytana wartosc powinna byc pusta "
                  << "(i="<< i << ", key="<< key <<", check=" << check << ")";
      }
    }
#endif
    delete DA1;
    delete DA2;
  }


  {
    cout << "\nMSG   : iterator++ 15 elementow.";
    TEST_MAP::const_iterator it1; //,it2;
    short il = 0;

    DA1 = new TEST_MAP;
    for( key = 1; key <= 15; key++ )
    {
      val_str = to_string( key );
      DA1->insert( make_pair( key, val_str ) );
    }
    //DA2 = new TEST_MAP;
    //for( key = 15; key >= 1; key-- )
    //{
    //   val_str = to_string( key_arr[key-1] );
    //   DA2->insert( make_pair( key_arr[key-1], val_str ) );
    //}

    for( it1 = DA1->begin(); it1 != DA1->end(); ++it1 )
    {
      ++il;
      if( il > 15 )
        ERR(65) << "Za duzo.";
    }
    if( il < 15 )
      ERR(67) << "Za malo.";

  }

#ifdef DWA_KIERUNKI
  {
    cout << "\nMSG   : iterator++, iterator--  15 elementow.";
    TEST_MAP::const_iterator it1; //,it2;

    DA1 = new TEST_MAP;
    for( key = 1; key <= 15; key++ )
    {
      val_str = to_string( key );
      DA1->insert( make_pair( key, val_str ) );
    }

    for( it1 = DA1->begin(); it1 != DA1->end(); ++it1 )
    {
      TEST_MAP::const_iterator it3;
      it3 = it1;
      ++it3;
      --it3;
      if( it3 == DA1->end() || it1->first != it3->first )
        ERR(71) << "*it != *(--++it)";
    }

    if(  ++--DA1->end() != DA1->end() )
      ERR(72) << "++--DA1->end() != DA1->end()";

    if(  --DA1->end() == DA1->end() )
      ERR(73) << "--DA1->end() == DA1->end()";
    else
      for( it1 = --DA1->end(); it1 != DA1->begin(); --it1 )
      {
        TEST_MAP::const_iterator it3;
        it3 = it1;
        --it3;
        ++it3;
        if( *it1 != *it3 )
          ERR(75) << "*it != *(++--it)";
      }

    delete DA1;
  }
#endif

  /* ---------------------------------------------------------------------------------------------------------*/
  /* ERR 97,98,99                                                                                             */

  DA=new TEST_MAP;
  DA->insert(make_pair(1,string("1")));
  if (CCount::getCount()<=0)
    ERR(98) << "CCount: Jeszcze nie zwolniono calej pamieci. CCount twierdzi, ze juz tak\n";
  delete DA;

  cout << "\n\nIlosc wykrytych bledow: " << errCnt << std::endl;
  return 0;
}

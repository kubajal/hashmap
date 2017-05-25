/**
   Zawiera deklaracje klasy ListMap.
   Jest to mapa (Slownik) zrobiona na liscie/pierscieniu.
   Implementacja tej klasy jest przedmiotem cwiczenia na laboratoriach z AISDI.

   COPYRIGHT:
   Copyright (c) 2015 Instytut Informatyki, Politechnika Warszawska
   ALL RIGHTS RESERVED
*******************************************************************************/

#include <cassert>
#include <cstddef>
#include <iterator>
#include <string>

/// Prosty licznik do podstawowej kontroli wyciekoww pamieci
class CCount
{
protected:
  static int count;
  CCount() { count++; }
  virtual ~CCount()
  {
    assert(count > 0);
    count--;
  }

public:
  static int getCount() { return count; }
};

//////////////////////////////////////////////////////////////////////////////
// ListMap i zwiazane klasy
//////////////////////////////////////////////////////////////////////////////

/// Klasa reprezentujaca wezel listy
struct ListNode : CCount
{
  typedef std::pair<int,std::string> T;
  ListNode* next;
  ListNode* prev;
  T data;
  ListNode(const T& d) : next(NULL), prev(NULL), data(d) {}
  ListNode(const T& d, ListNode* n, ListNode* p) : next(n), prev(p), data(d) {}
};

/// Mapa z metodami jak std::map.
/// Mapa powinna zostac zaimplementowana jako lista lub pierscien
/// w wersji jedno- lub dwukierunkowej zgodnie z wytycznymi prowadzacych.
class ListMap
{
public:
  typedef int Key;
  typedef std::string Val;

protected:
  typedef ListNode Node;
  Node* first;
  Node* last;

public:
  typedef std::size_t size_type;
  typedef std::pair<Key, Val> P;

  ListMap();
  ListMap(const ListMap& other);
  ~ListMap();

  class const_iterator : public std::iterator<std::forward_iterator_tag,
                                              std::pair<Key, Val> >
  {
    friend class ListMap;
  public:
    typedef std::pair<Key, Val> T;

  protected:
    Node* node;
    ListMap* map;

    const_iterator(Node* x, ListMap* m) : node(x), map(m) {}

  public:
    const_iterator() {}
    const_iterator(const const_iterator& a) : node(a.node), map(a.map) {}

    const T& operator*() const
    {
      return node->data;
    }

    const T* operator->() const
    {
      return &(node->data);
    }

    const_iterator& operator++();   // pre
    const_iterator operator++(int); // post
    const_iterator& operator--();   // pre
    const_iterator operator--(int); // post

    bool operator==(const const_iterator& a) const
    {
      return map == a.map && node == a.node;
    }

    bool operator!=(const const_iterator& a) const
    {
      return map != a.map || node != a.node;
    }
  };

  class iterator : public const_iterator
  {
    friend class ListMap;
    iterator(Node* x, ListMap* m) : const_iterator(x, m) {}

  public:
    iterator() {}
    iterator(const iterator& a) : const_iterator(a) {}

    T& operator*() const
    {
      return node->data;
    }

    T* operator->() const
    {
      return &(node->data);
    }

    iterator& operator++()   // pre
    {
      const_iterator::operator++();
      return *this;
    }

    iterator operator++(int) // post
    {
      iterator temp = *this;
      ++*this;
      return temp;
    }

    iterator& operator--()   // pre
    {
      const_iterator::operator--();
      return (*this);
    }

    iterator operator--(int) // post
    {
      iterator temp = *this;
      --*this;
      return temp;
    }
  };

  iterator begin();
  const_iterator begin() const;

  iterator end();
  const_iterator end() const;

  /// Wstawienie elementu do mapy.
  /// @returns Para, ktorej komponent bool jest rowny true gdy wstawienie zostalo
  ///          dokonane, a false gdy element identyfikowany przez klucz
  ///          juz istnial w mapie. Iterator ustawiony jest na ten wstawiony
  ///          lub istniejacy juz w mapie element.
  std::pair<iterator, bool> insert(const std::pair<Key, Val>& entry);

  /// Wstawienie elementu do mapy.
  /// Matoda zaklada, ze w mapie nie wystepuje element identyfikowany przez key
  iterator unsafe_insert(const std::pair<Key, Val>& entry);

  /// Zwraca iterator addresujacy element w mapie dla ktorego klucz jest rowny
  /// szukanemu kluczowi lub element za ostatnim gdy szukanego klucza brak w mapie.
  iterator find(const Key& k);
  const_iterator find(const Key& k) const;

  /// Udostepnia wartosc powiazana z kluczem key. Wstawia element do mapy jesli
  /// nie istnial.
  /// @returns Referencje do wartosci powiazanej z kluczem.
  Val& operator[](const Key& k);

  bool empty() const;
  size_type size() const;

  /// Zwraza ilosc elementow skojarzonych z kluczem key.
  size_type count(const Key& _Key) const;

  /// Usuwa element z mapy.
  /// @returns iterator adresujacy pierwszy element za usuwanym.
  iterator erase(iterator i);

  /// Usuwa zakres elementow z mapy.
  /// Zakres jest zdefiniowany poprzez iteratory first i last
  /// first jest okresla pierwszy element do usuniecia, a last okresla element
  /// po ostatnim usunietym elemencie.
  /// @returns iterator adresujacy pierwszy element za usuwanym.
  iterator erase(iterator first, iterator last);

  /// Usuwa element z mapy.
  /// @returns Ilosc usunietych elementow (0 lub 1).
  size_type erase(const Key& key);

  /// Usuniecie wszystkich elementow z mapy.
  void clear();

  /// Porownanie strukturalne map.
  /// Czy reprezentacja danych jest identyczna.
  bool struct_eq(const ListMap& another) const;
  /// Porownanie informacyjne map.
  /// Czy informacje trzymane w mapach sa identyczne.
  bool info_eq(const ListMap& another) const;
};

inline bool operator==(const ListMap& a, const ListMap& b)
{
  return a.info_eq(b);
}


#ifndef RBASE_H
#define RBASE_H

#include "File.h"

class IReadRBase
{
private:
    virtual IReadSeekFile & getFile () const = 0;
protected:
    bool file_is_valid;
    nat32 rsize, position;
public:
    bool isValid () const { return file_is_valid; }
    void invalidate () { file_is_valid = false; }
    bool first ();
    bool  next ();
    nat32 size () const;
    nat32 read ( nat32 n, void * p, nat32 shift ) const;
};

class ReadRBase : public IReadRBase
{
private:
    IReadSeekFile & file;
    virtual IReadSeekFile & getFile () const { return file; }
// Запрет конструктора копии и оператора присваивания:
    ReadRBase ( ReadRBase & );
    void operator = ( ReadRBase & );
public:
    explicit ReadRBase ( IReadSeekFile & p );
};

class RBase : public IReadRBase
{
private:
    IFile & file;
    virtual IReadSeekFile & getFile () const { return file; }
// Запрет конструктора копии и оператора присваивания:
    RBase ( RBase & );
    void operator = ( RBase & );
public:
    explicit RBase ( IFile & p );
    nat32 write ( nat32 n, const void * p, nat32 shift );
    nat32 add   ( nat32 n, const void * p );
};

///////////////////////////////////////////////////////////////////////////////

class RBL2_Header
{
public:
    nat32 type;
    nat32 flag;
};

class ReadRBaseLay2
{
    ReadRBase base;
// Запрет конструктора копии и оператора присваивания:
    ReadRBaseLay2 ( ReadRBaseLay2 & );
    void operator = ( ReadRBaseLay2 & );
public:
    explicit ReadRBaseLay2 ( IReadSeekFile & file );

    bool isValid () const { return base.isValid(); }
    bool first ();
    bool  next ();
    nat32 size () const;
    bool  read  ( RBL2_Header & head ) const;
    nat32 read  ( nat32 n, void * p, nat32 shift ) const;
};

class RBaseLay2
{
    RBase base;
// Запрет конструктора копии и оператора присваивания:
    RBaseLay2 ( RBaseLay2 & );
    void operator = ( RBaseLay2 & );
public:
    explicit RBaseLay2 ( IFile & file );

    bool isValid () const { return base.isValid(); }
    bool first ();
    bool  next ();
    nat32 size () const;
    bool  read  ( RBL2_Header & head ) const;
    nat32 read  ( nat32 n, void * p, nat32 shift ) const;
    bool  write ( const RBL2_Header & head, nat32 n, const void * p, nat32 shift );
    bool  add   ( const RBL2_Header & head, nat32 n, const void * p );
};

///////////////////////////////////////////////////////////////////////////////

#endif
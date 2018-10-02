
#include "RBase.h"

bool IReadRBase::first()
{
    if ( ! file_is_valid ) return false;
    IReadSeekFile & file = getFile();
    file.seek_set ( 8 );
    if ( file.read ( &rsize, 4, 1 ) != 1 ) return false;
    position = 12;
    return true;
}

bool IReadRBase::next ()
{
    if ( ! file_is_valid || position == 0 ) return false;
    IReadSeekFile & file = getFile();
    file.seek_set ( position + rsize );
    nat32 ns;
    if ( file.read ( &ns, 4, 1 ) != 1 )
    {
        position = 0;
        return false;
    }
    position += rsize + 4;
    rsize = ns;
    return true;
}

nat32 IReadRBase::size () const
{
    if ( ! file_is_valid || position == 0 ) return 0;
    return rsize;
}

nat32 IReadRBase::read ( nat32 n, void * p, nat32 shift ) const
{
    if ( ! file_is_valid || position == 0 ) return 0;
    if ( n + shift > rsize )
    {
        if ( shift >= rsize ) return 0;
        n = rsize - shift;
    }
    IReadSeekFile & file = getFile();
    file.seek_set ( position + shift );
    return file.read ( p, 1, n );
}

///////////////////////////////////////////////////////////////////////////////

static const nat32 nRBase1[2] = {1935753810, 538980709}; // "RBase1  "

ReadRBase::ReadRBase ( IReadSeekFile & p ) : file ( p )
{
    position = 0;
    nat32 n[2] = { 0, 0 };
    file.seek_set ( 0 );
    file.read ( n, 4, 2 );
    file_is_valid = n[0] == nRBase1[0] && n[1] == nRBase1[1];
}

///////////////////////////////////////////////////////////////////////////////

RBase::RBase ( IFile & p ) : file ( p )
{
    position = 0;
    if ( ! file.seek_end(0) )
    {
        file_is_valid = false;
        return;
    }
    if ( file.tell() == 0 )
    {
        if ( file.write ( nRBase1, 1, 8 ) != 8 )
        {
            file_is_valid = false;
        }
        else
        {
            file_is_valid = true;
        }
        return;
    }
    nat32 n[2] = { 0, 0 };
    file.seek_set ( 0 );
    file.read ( n, 4, 2 );
    file_is_valid = n[0] == nRBase1[0] && n[1] == nRBase1[1];
}

nat32 RBase::write ( nat32 n, const void * p, nat32 shift )
{
    if ( ! file_is_valid || position == 0 ) return 0;
    if ( n + shift > rsize )
    {
        if ( shift >= rsize ) return 0;
        n = rsize - shift;
    }
    file.seek_set ( position + shift );
    return file.write ( p, 1, n );
}

nat32 RBase::add ( nat32 n, const void * p )
{
    if ( ! file_is_valid ) return 0;
    file.seek_end ( 0 );
    if ( file.write ( &n, 4, 1 ) == 0 ) return 0;
    position = file.tell ();
    rsize = file.write ( p, 1, n );
    if ( rsize != n )
    {
        file.seek_set ( position - 4 );
        file.write ( &rsize, 4, 1 );
    }
    return rsize;
}

///////////////////////////////////////////////////////////////////////////////

static const nat32 nRBLay2v1[2] = { 1632387666, 829829753 }; // "RBLay2v1"

ReadRBaseLay2::ReadRBaseLay2 ( IReadSeekFile & file ) : base ( file )
{
    if ( ! base.isValid() ) return;
    if ( base.first() )
    {
        nat32 tmp[2];
        if ( base.read ( 8, tmp, 0 ) == 8 && tmp[0] == nRBLay2v1[0] && tmp[1] == nRBLay2v1[1] ) return;
    }
    base.invalidate();
}

bool ReadRBaseLay2::first()
{
    return base.first() && base.next();
}

bool ReadRBaseLay2::next()
{
    return base.next();
}

nat32 ReadRBaseLay2::size() const
{
    const nat32 n = base.size();
    return n > 8 ? n - 8 : 0;
}

bool ReadRBaseLay2::read ( RBL2_Header & head ) const
{
    return base.read ( 8, &head, 0 ) == 8;
}

nat32 ReadRBaseLay2::read ( nat32 n, void * p, nat32 shift ) const
{
    return base.read ( n, p, shift+8 );
}

///////////////////////////////////////////////////////////////////////////////

RBaseLay2::RBaseLay2 ( IFile & file ) : base ( file )
{
    if ( ! base.isValid() ) return;
    if ( base.first() )
    {
        nat32 tmp[2];
        if ( base.read ( 8, tmp, 0 ) == 8 && tmp[0] == nRBLay2v1[0] && tmp[1] == nRBLay2v1[1] ) return;
    }
    else
    {
        if ( base.add ( 8, nRBLay2v1 ) == 8 ) return;
    }
    base.invalidate();
}

bool RBaseLay2::first()
{
    return base.first() && base.next();
}

bool RBaseLay2::next()
{
    return base.next();
}

nat32 RBaseLay2::size() const
{
    const nat32 n = base.size();
    return n > 8 ? n - 8 : 0;
}

bool RBaseLay2::read ( RBL2_Header & head ) const
{
    return base.read ( 8, &head, 0 ) == 8;
}

nat32 RBaseLay2::read ( nat32 n, void * p, nat32 shift ) const
{
    return base.read ( n, p, shift+8 );
}

bool RBaseLay2::write ( const RBL2_Header & head, nat32 n, const void * p, nat32 shift )
{
    return base.write ( 8, &head, 0 ) == 8 && base.write ( n, p, shift+8 ) == n;
}

bool RBaseLay2::add ( const RBL2_Header & head, nat32 n, const void * p )
{
    if ( n == 0 )
    {
        return base.add ( 8, &head ) == 8;
    }
    return base.add ( n + 8, (const char*) p - 8 ) == n + 8 && base.write ( 8, &head, 0 ) == 8;
}
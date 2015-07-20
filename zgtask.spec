Name:		zgtask
Version:	0.1.0
Release:	1%{?dist}
Summary:	Task manager using ZeroMQ and Git
Group:		System Environment/Libraries
License:	LGPL v3+
Source0:    %{name}-%{version}.tar.gz

BuildRequires:  cmake, czmq-devel
Requires: git

%description
Task manager using ZeroMQ and Git.

%prep
%setup -q

%build
./configure
make %{?_smp_mflags}
cd ../

%install
rm -rf %{buildroot}
cd build
make install DESTDIR=%{buildroot}

%files
#%{_bindir}/zgt
#%{_bindir}/zgt-submit
#%{_bindir}/zgt-merge-root

%changelog

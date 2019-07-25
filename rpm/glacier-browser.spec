%{!?qtc_qmake:%define qtc_qmake %qmake}
%{!?qtc_qmake5:%define qtc_qmake5 %qmake5}
%{!?qtc_make:%define qtc_make make}
%{?qtc_builddir:%define _builddir %qtc_builddir}

Name:       glacier-browser
Summary:    Web browser for glacier UX
Version:    0.1
Release:    1
Group:      Qt/Qt
License:    LICENSE
URL:        https://github.com/nemomobile-ux/glacier-browser
Source0:    %{name}-%{version}.tar.bz2

Requires: qt5-qtquickcontrols-nemo
Requires: libglacierapp
Requires: qt5-qtqml-import-webkitplugin
# TODO: migrate to webengineplugin when it will correct build
#Requires: qt5-qtqml-import-webengineplugin

BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  desktop-file-utils
BuildRequires:  qt5-qttools-linguist
BuildRequires:  pkgconfig(glacierapp)

%description
Default browser for glacier ux

%prep
%setup -q -n %{name}-%{version}

%build
%qtc_qmake5
%qtc_make %{?_smp_mflags}

%install
rm -rf %{buildroot}
%qmake5_install

lrelease %{buildroot}%{_datadir}/%{name}/translations/*.ts

desktop-file-install --delete-original       \
  --dir %{buildroot}%{_datadir}/applications             \
   %{buildroot}%{_datadir}/applications/*.desktop

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop

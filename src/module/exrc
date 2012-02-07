if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <silent> <S-Tab> =BackwardsSnippet()
snoremap <silent> 	 i<Right>=TriggerSnippet()
snoremap  b<BS>
snoremap % b<BS>%
snoremap ' b<BS>'
imap ð :call SearchInvalidComment(1)a
imap î :call SearchInvalidComment(0)a
imap ã :call JCommentWriter()
map Q gq
snoremap U b<BS>U
snoremap \ b<BS>\
snoremap ^ b<BS>^
snoremap ` b<BS>`
nmap gx <Plug>NetrwBrowseX
snoremap <Left> bi
snoremap <Right> a
snoremap <BS> b<BS>
snoremap <silent> <S-Tab> i<Right>=BackwardsSnippet()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
map <C-F12> :!ctags -R --sort=yes --c++-kinds=+p --fields=+iaS --extra=+q .
inoremap <silent> 	 =TriggerSnippet()
inoremap <silent> 	 =ShowAvailableSnips()
inoremap <expr>  omni#cpp#maycomplete#Complete()
inoremap <expr> . omni#cpp#maycomplete#Dot()
inoremap <expr> : omni#cpp#maycomplete#Scope()
inoremap <expr> > omni#cpp#maycomplete#Arrow()
map ð :call SearchInvalidComment(1)
map î :call SearchInvalidComment(0)
map ã :call JCommentWriter()
iabbr }- }h%?\w:nohl:call JCommentWriter()
let &cpo=s:cpo_save
unlet s:cpo_save
set autochdir
set autoindent
set backspace=2
set backupdir=~/.vim/tmp/bac
set breakat=
set complete=.,k,b,t
set completefunc=VjdeCppCFU0
set completeopt=menuone,longest,preview
set dictionary=/usr/share/dict/words
set directory=~/.vim/tmp/swp
set expandtab
set fileencodings=utf8,cp1251
set helplang=en
set hidden
set history=50
set hlsearch
set incsearch
set langmap=ФИСВУАПРШОЛДЬТЩЗЙКЫЕГМЦЧНЯЖ;ABCDEFGHIJKLMNOPQRSTUVWXYZ:,фисвуап��шолдьтщзйкыегмцчня;abcdefghijklmnopqrstuvwxyz
set laststatus=2
set listchars=tab:»\ ,trail:·,extends:→,precedes:←,nbsp:×
set nomodeline
set mouse=a
set mousemodel=popup
set omnifunc=omni#cpp#complete#Main
set ruler
set runtimepath=~/.vim,~/.vim/bundle/NERDTree,~/.vim/bundle/omnicppcomplete,~/.vim/bundle/snipMate,~/.vim/bundle/taglist,/usr/share/vim/vimfiles,/usr/share/vim/vim73,/usr/share/vim/vimfiles/after,~/.vim/bundle/omnicppcomplete/after,~/.vim/bundle/snipMate/after,~/.vim/after
set shiftwidth=4
set showmatch
set showtabline=2
set smartindent
set smarttab
set statusline=%<%f%h%m%r\ %b\ %{&encoding}\ 0x\ \ %l,%c%V\ %P
set suffixes=.bak,~,.o,.h,.info,.swp,.obj,.info,.aux,.log,.dvi,.bbl,.out,.o,.lo
set tabstop=4
set tags=./tags,./TAGS,tags,TAGS,~/.vim/tags/cpp
set termencoding=utf-8
set title
set undodir=~/.vim/tmp/undo/
set undofile
set viminfo='20,\"500
set wildmenu
" vim: set ft=vim :

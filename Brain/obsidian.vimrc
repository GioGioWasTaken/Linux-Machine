" Custom vimrc file for obsidian navigation. 


" Remap for dealing with word wrap
nmap j gj 
nmap k gk

" Non-recursive mapping for normal mode
nnoremap ss :noh<CR>

" Recursive mapping for insert mode
imap qq <Esc>

" Recursive mapping for normal mode
map <C-e> $
map <C-b> ^

"" Remap for dealing with word wrap
nnoremap <expr> k (v:count == 0 ? 'gk' : 'k')
nnoremap <expr> j (v:count == 0 ? 'gj' : 'j')
" Yank to system clipboard
set clipboard=unnamed

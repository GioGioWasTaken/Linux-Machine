vim.api.nvim_set_keymap("i", "jj", "<Esc>", {noremap=false})
-- twilight
vim.api.nvim_set_keymap("n", "tw", ":Twilight<enter>", {noremap=false})
-- buffers
vim.api.nvim_set_keymap("n", "tG", ":blast<enter>", {noremap=false})
vim.api.nvim_set_keymap("n", "tgg", ":bfirst<enter>", {noremap=false})
vim.api.nvim_set_keymap("n", "th", ":bprev<enter>", {noremap=false})
vim.api.nvim_set_keymap("n", "tl", ":bnext<enter>", {noremap=false})
vim.api.nvim_set_keymap("n", "td", ":bdelete<enter>", {noremap=false})
-- files
vim.api.nvim_set_keymap("n", "QQ", ":q!<enter>", {noremap=false})
vim.api.nvim_set_keymap("n", "WW", ":w!<enter>", {noremap=false})
vim.api.nvim_set_keymap("n", "<C-e>", "$", {noremap=false})
vim.api.nvim_set_keymap("n", "<C-b>", "^", {noremap=false})
vim.api.nvim_set_keymap("n", "TT", ":TransparentToggle<CR>", {noremap=true})
vim.api.nvim_set_keymap("n", "ss", ":noh<CR>", {noremap=true})
-- stop highlighting of words (for example by / or ?)
vim.api.nvim_set_keymap("n", "<C-s>", ":w<CR>", {noremap=true, silent=true})
vim.api.nvim_set_keymap("n", "<C-c>", ":%y<CR>", {noremap=true, silent=true})


-- my terminal shortcuts
vim.api.nvim_set_keymap("n", "vv", ":rightbelow vertical terminal<CR>", { noremap = true, silent = true })
vim.api.nvim_set_keymap ('t', '<Esc>', "<C-\\><C-N>",  {silent = true })



-- Move to the left split
vim.api.nvim_set_keymap("n", "<C-h>", "<C-w>h", { noremap = true, silent = true })
vim.api.nvim_set_keymap("t", "<C-h>", "<C-\\><C-n><C-w>h", { noremap = true, silent = true })

-- Move to the split below
vim.api.nvim_set_keymap("n", "<C-j>", "<C-w>j", { noremap = true, silent = true })
vim.api.nvim_set_keymap("t", "<C-j>", "<C-\\><C-n><C-w>j", { noremap = true, silent = true })

-- Move to the split above
vim.api.nvim_set_keymap("n", "<C-k>", "<C-w>k", { noremap = true, silent = true })
vim.api.nvim_set_keymap("t", "<C-k>", "<C-\\><C-n><C-w>k", { noremap = true, silent = true })

-- Move to the right split
vim.api.nvim_set_keymap("n", "<C-l>", "<C-w>l", { noremap = true, silent = true })
-- we have to get rid of the C-l remap, since it interferes with terminal shortcut, but my terminal is always my rightmost window, so it's fine.
-- vim.api.nvim_set_keymap("t", "<C-l>", "<C-\\><C-n><C-w>l", { noremap = true, silent = true })




-- Noice
vim.api.nvim_set_keymap("n", "<C-y>", ":Noice dismiss<CR>", {noremap=true})

-- vim.keymap.set("n", "<leader>ee", "<cmd>GoIfErr<cr>", {silent = true, noremap = true}) -- idk what this does

      -- splits

      vim.api.nvim_set_keymap("n", "<C-,>", ":vertical resize -10<CR>", {noremap=true})
      vim.api.nvim_set_keymap("n", "<C-.>", ":vertical resize +10<CR>", {noremap=true})
      -- Quicker close split
      vim.keymap.set("n", "<leader>qq", ":q<CR>", {silent = true, noremap = true})


      -- vim.keymap.set('n', '<space><space>', "<cmd>set nohlsearch<CR>")



      -- Keymaps for better default experience
      -- See `:help vim.keymap.set()`
      vim.keymap.set({ 'n', 'v' }, '<Space>', '<Nop>', { silent = true }) -- free space bar as leader key
      --
      -- Remap for dealing with word wrap
      vim.keymap.set('n', 'k', "v:count == 0 ? 'gk' : 'k'", { expr = true, silent = true })
      vim.keymap.set('n', 'j', "v:count == 0 ? 'gj' : 'j'", { expr = true, silent = true })


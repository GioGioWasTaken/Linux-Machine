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
vim.api.nvim_set_keymap("n", "E", "$", {noremap=false})
vim.api.nvim_set_keymap("n", "B", "^", {noremap=false})
vim.api.nvim_set_keymap("n", "TT", ":TransparentToggle<CR>", {noremap=true})
vim.api.nvim_set_keymap("n", "ss", ":noh<CR>", {noremap=true})
-- stop highlighting of words (for example by / or ?)



-- Noice
vim.api.nvim_set_keymap("n", "<C-y>", ":NoiceDismiss<CR>", {noremap=true})

vim.keymap.set("n", "<leader>ee", "<cmd>GoIfErr<cr>",
  {silent = true, noremap = true}

-- stuff I don't understand so i commented out:
  --
      -- -- splits
      -- --
      -- vim.api.nvim_set_keymap("n", "<C-W>,", ":vertical resize -10<CR>", {noremap=true})
      -- vim.api.nvim_set_keymap("n", "<C-W>.", ":vertical resize +10<CR>", {noremap=true})
      --
      --
      --
      -- vim.keymap.set('n', '<space><space>', "<cmd>set nohlsearch<CR>")
      --
      --
      -- -- Quicker close split
      -- vim.keymap.set("n", "<leader>qq", ":q<CR>",
      --   {silent = true, noremap = true}
      -- )
      --
      -- -- Keymaps for better default experience
      -- -- See `:help vim.keymap.set()`
      -- vim.keymap.set({ 'n', 'v' }, '<Space>', '<Nop>', { silent = true })
      --
      -- -- Remap for dealing with word wrap
      -- vim.keymap.set('n', 'k', "v:count == 0 ? 'gk' : 'k'", { expr = true, silent = true })
      -- vim.keymap.set('n', 'j', "v:count == 0 ? 'gj' : 'j'", { expr = true, silent = true })
)
local base = require("plugins.configs.lspconfig")
local on_attach = base.on_attach
local capabilities = base.capabilities

local lspconfig = require("lspconfig")

lspconfig.clangd.setup {
  on_attach = function(client, bufnr)
    client.server_capabilities.signatureHelpProvider = false
    on_attach(client, bufnr)
  end,
  capabilities = capabilities,
}
-- clangd has a bug that has to be fixed manually, so it's exempted from the servers for loop below.

local servers = { "marksman", "jdtls", "pyright", "bashls"}
for _, lsp in ipairs(servers) do
  lspconfig[lsp].setup {
    -- on_init = on_init,
    on_attach = on_attach,
    capabilities = capabilities,
  }
end
lspconfig.pyright.setup {
  filetypes= {"python"}
}
lspconfig.jdtls.setup {
  filetypes= {"java"}
}

/// Vendor Modules
import * as fumadocs from 'fumadocs-mdx/next';

// Next JS Configuration.
export default fumadocs.createMDX()({
    output: 'export',
    reactStrictMode: true,
});

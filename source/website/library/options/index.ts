/// Vendor Modules
import { BaseLayoutProps } from 'fumadocs-ui/layouts/shared';

/// Website Modules
import { Product } from '@/website/product';

/** Core Layout Properties. */
export interface Options extends Omit<BaseLayoutProps, 'children'> {}
export function Options(overrides: Options = {}): Options {
    return {
        githubUrl: Product.github,
        nav: { title: Product.shortName },
        ...overrides,
    };
}
